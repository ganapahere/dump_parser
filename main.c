#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: ./a.out <path_to_mem_dump_file>\n");
		exit(EXIT_SUCCESS);
	}

	printf("active process count = %u\n", get_active_process_count(argv[1]));

	exit(EXIT_SUCCESS);
}
