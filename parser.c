#include "parser.h"

unsigned int get_active_process_count(char *path_mem_dump)
{
	int fd, ret;
	unsigned int addr;
	struct stat s_stat;
	unsigned int count;
	pdir_t *p_pdir;

	assert(path_mem_dump != NULL);
	fd = open(path_mem_dump, O_RDONLY);
	assert(fd != -1);

	ret = fstat(fd, &s_stat);
	assert(ret != -1);

	count = 0;
	for (addr = 0; addr < s_stat.st_size; addr += PDIR_SIZE) {
		p_pdir = get_pdir(fd, addr);
		fill_valid_pde_count(p_pdir);
		if (is_valid_pdir(p_pdir)) {
			count++;
		}
		put_pdir(p_pdir);
	}

	return count;
}

static pdir_t *get_pdir(int fd, unsigned int pdir_addr)
{
	int ret;
	pdir_t *p_pdir;

	p_pdir = calloc(1, sizeof(pdir_t));
	assert(p_pdir != NULL);
	p_pdir->pde_ptr = mmap(NULL, PDIR_SIZE, PROT_READ, MAP_PRIVATE, fd, pdir_addr);
	if (p_pdir->pde_ptr == NULL) {
		free(p_pdir);
		return NULL;
	}

	return p_pdir;
}

static void fill_valid_pde_count(pdir_t *p_pdir)
{
	int i;

	for (i = KERN_PDE_START; i < NUM_PDE; i++) {
		if ((p_pdir->pde_ptr[i] & PDE_FLAG_MASK) == KERN_PDE_SIG) {
			p_pdir->pde_match++;
		}
	}

}

static bool is_valid_pdir(pdir_t *p_pdir)
{
	if (p_pdir->pde_match >= KERN_PDE_THR) {
		return true;
	}

	return false;
}

static void put_pdir(pdir_t *p_pdir)
{
	assert(p_pdir != NULL && p_pdir->pde_ptr != NULL);
	munmap(p_pdir->pde_ptr, PDIR_SIZE);
	free(p_pdir);
}
