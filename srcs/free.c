#include "private_malloc.h"

void	free(void *ptr)
{
	t_header_block	*block;

	if (ptr == 0)
		return ;
	block = ptr - sizeof(t_header_block);
	block->is_free = 1;
	PAGE(block->page)->capacity += block->size;
	apply_buddy_check(
		&((t_header_block *)(block - sizeof(t_header_block)))->list);
}