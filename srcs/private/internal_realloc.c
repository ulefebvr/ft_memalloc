#include "malloc.h"
#include "private_malloc.h"

void			*internal_realloc(
	t_header_page *page, t_header_block *block, void *ptr, size_t size)
{
	void		*tmp;

	if (page && get_type(size) == get_type(page->type))
	{
		block->size = size;
		return (ptr);
	}
	else if ((tmp = malloc(size)))
	{
		ft_memcpy(tmp, block->ptr, block->size < size ? block->size : size);
		free(block->ptr);
		return (tmp);
	}
	return (ptr);
}
