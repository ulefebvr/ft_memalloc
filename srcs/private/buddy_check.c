#include "private_malloc.h"

void apply_buddy_check(t_lst *block)
{
	if (block->next && BLOCK(block->next)->is_free)
		join_block(block, block->next);
	else if (block->prev && BLOCK(block->prev)->is_free)
		join_block(block->prev, block);
}
