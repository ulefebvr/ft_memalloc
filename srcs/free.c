#include "private_malloc.h"

void		free(void *ptr)
{
	t_header_page	*page;
	t_header_block	*block;

	if (ptr == 0 || (!(page = check_ptr_page(ptr)) 
		&& !(block = check_ptr_block(page, ptr))))
		return ;
	internal_free(page, block);
}
