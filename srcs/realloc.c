#include "malloc.h"
#include "private_malloc.h"

void		*realloc(void *ptr, size_t size)
{
	t_header_page	*page;
	t_header_block	*block;

	if (ptr == 0)
		return (malloc(size));
	else if ((!(page = check_ptr_page(ptr)) 
		&& !(block = check_ptr_block(page, ptr))))
		return (0);
	else if (size == 0)
	{
		free(ptr);
		return (0);
	}
	return (internal_realloc(page, block, ptr, size));
}
