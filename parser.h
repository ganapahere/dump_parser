#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdbool.h>

#define NUM_PDE		1024
#define PDE_SIZE	4
#define PDIR_SIZE	(PDE_SIZE * NUM_PDE)
#define KERN_PDE_START	768
#define PDE_FLAG_MASK	0x0000FFFF
#define KERN_PDE_SIG	0x000001E3
#define KERN_PDE_THR	219

typedef struct pdir {
	unsigned int pdir_addr;
	unsigned int pde_match;
	unsigned int zero_match;
	unsigned int *pde_ptr;
} pdir_t;

unsigned int get_active_process_count(char *path_mem_dump);

static pdir_t *get_pdir(int fd_dump, unsigned int pdir_addr);
static void fill_valid_pde_count(pdir_t *p_pdir);
static bool is_valid_pdir(pdir_t *p_pdir);
static void put_pdir(pdir_t *p_pdir);
#endif
