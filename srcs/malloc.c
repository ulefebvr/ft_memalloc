#include "private_malloc.h"

void *malloc(size_t size)
{
	t_lst			*block;

	if (size <= 0 || (!g_malloc.init && malloc_initialize() <= 0))
		return (0);
	if (!(block = malloc_getblock(size)))
		return (0);
	return ((void *)BLOCK(block) + sizeof(t_header_block));
}
