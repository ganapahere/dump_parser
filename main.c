#include "stdio.h"
#include "assert.h"
#include <sys/stat.h>
#include "fcntl.h"
#include <sys/mman.h>
#include "stdlib.h"
#include "errno.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
	int fd;
	unsigned char *p_buf;
	struct stat s_stat;
	int ret;
	int i;
	unsigned int t1, t2, t3, t4, _t1, _t2, _t3, _t4;

	fd = open("fmem.bin", O_RDONLY);
	assert(fd != -1);

	ret = fstat(fd, &s_stat);
	assert(ret != -1);

	//p_buf = mmap(NULL, s_stat.st_size, PROT_READ, MAP_PRIVATE, fd, getpagesize());
	p_buf = mmap(NULL, getpagesize(), PROT_READ, MAP_PRIVATE, fd, 0);
	assert(p_buf != NULL && p_buf != MAP_FAILED);
	for (i = 0; i < (getpagesize() / sizeof(unsigned int));) {
		//printf("%02hhx ", p_buf[i]);
		t1 = *((unsigned int *)p_buf + i);
		t2 = *((unsigned int *)p_buf + i + 1);
		t3 = *((unsigned int *)p_buf + i + 2);
		t4 = *((unsigned int *)p_buf + i + 3);

#if 0
		_t1 = ((t1 & 0xff) << 24) | ((t1 & 0xff000000) >> 24) | ((t1 & 0x00ff0000) >> 8) | ((t1 & 0x0000ff00) << 8);
		_t2 = ((t2 & 0xff) << 24) | ((t2 & 0xff000000) >> 24) | ((t2 & 0x00ff0000) >> 8) | ((t2 & 0x0000ff00) << 8);
		_t3 = ((t3 & 0xff) << 24) | ((t3 & 0xff000000) >> 24) | ((t3 & 0x00ff0000) >> 8) | ((t3 & 0x0000ff00) << 8);
		_t4 = ((t4 & 0xff) << 24) | ((t4 & 0xff000000) >> 24) | ((t4 & 0x00ff0000) >> 8) | ((t4 & 0x0000ff00) << 8);
		printf("%08x %08x %08x %08x\n", _t1, _t2, _t3, _t4);
#endif
#if 0
		       *((unsigned int *)p_buf + i),
		       *((unsigned int *)p_buf + i + 1),
		       *((unsigned int *)p_buf + i + 2),
		       *((unsigned int *)p_buf + i + 3));
#endif
		i = i + 4;
	}
	printf("\n");

	exit(0);
}
