#include "libft.h"
#include "private_malloc.h"

t_lst	*get_freed_block(size_t size, t_lst *page)
{
	t_lst *block;

	if (PAGE(page)->capacity > block_size(size) + sizeof(t_header_block))
	{
		block = &PAGE(page)->block;
		while (block)
		{
			// if (BLOCK(block)->is_free && BLOCK(block)->capacity >= size)
			if (BLOCK(block)->is_free)
				return (block);
			block = block->next;
		}
	}
	return (0);
}

void	reserve_block(t_lst *page, t_lst *block, size_t size)
{
	BLOCK(block)->size = block_size(size);
	BLOCK(block)->is_free = 0;
	PAGE(page)->capacity -= BLOCK(block)->size;
}

t_lst	*check_page(size_t size)
{
	t_lst	*page;
	size_t	block_size;

	page = *get_type(size);
	block_size = size;
	while (page)
	{
		if (PAGE(page)->capacity > block_size)
			return (page);
		// if (PAGE(page)->possibility > block_size)
		// 	return (page_defrag(page));
		page = page->next;
	}
	return (0);
}

t_lst	*malloc_getblock(size_t size)
{
	t_lst	*page;
	t_lst	*block;

	if ((page = check_page(size)))
	{
		ft_print("page with enough space\n");
		block = get_freed_block(size, page);
	}
	else if ((page = add_new_page(size)))
	{
		ft_print("page added\n");
		block = &PAGE(page)->block;
	}
	else
		return (0);
	split_block(page, block, size);
	reserve_block(page, block, size);
	return (block);
}
