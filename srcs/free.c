#include "private_malloc.h"

void	free(void *ptr)
{
	t_lst	*block;

	if (ptr == 0 || (block = check_adress(ptr)) == 0)
		return ;
	THREAD_SAFE_ACTIVATE;
	BLOCK(block)->is_free = 1;
	PAGE(BLOCK(block)->page)->capacity += BLOCK(block)->size;
	apply_buddy_check(block);
	THREAD_SAFE_DEACTIVATE;
}