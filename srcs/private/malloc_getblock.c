#include "libft.h"
#include "private_malloc.h"

t_lst	*get_freed_block(size_t size, t_lst *page)
{
	t_lst *tmp_block;
	t_lst *tmp_page;

	tmp_page = page;
	while (tmp_page)
	{
		if (PAGE(tmp_page)->capacity > block_size(size) + sizeof(t_header_block))
		{
			tmp_block = &PAGE(tmp_page)->block;
			while (tmp_block)
			{
				if (BLOCK(tmp_block)->is_free)
					return (tmp_block);
				tmp_block = tmp_block->next;
			}
		}
		tmp_page = tmp_page->next;
	}
	return (0);
}

t_lst	*get_page_from_block(t_lst *block)
{
	t_lst *head;

	head = lst_get_head(block);
	// ft_print("[[%s]]\n", BLOCK(head) + sizeof(t_header_block));
	return (&(CONTAINEROF(head, t_header_page, block)->list));
}

t_lst	*malloc_getblock(size_t size)
{
	t_lst	*page;
	t_lst	*block;

	page = *get_type(size);
	// if (page) ft_print("page_cpaa -> :: %d\n", (PAGE(page)->capacity));	
	block = get_freed_block(size, page);
	if (block)
	{
		// ft_print("block found\n");
		page = get_page_from_block(block);
	}

	// if (page) ft_print("page_cpaa -> :: %d\n", (PAGE(page)->capacity));
	
	if (!block)
	{
		// ft_fdprint(2, "add new page");
		page = add_new_page(size);
		// ft_fdprint(2, " :: added\n");
		block = &PAGE(page)->block;
	}
	// if (page) ft_print("page_cpaa -> :: %d\n", (PAGE(page)->capacity));
	split_block(page, block, size);
	BLOCK(block)->size = block_size(size);
	BLOCK(block)->is_free = 0;
	PAGE(page)->capacity -= BLOCK(block)->size;
	// ft_fdprint(2, "capa || block_size   %d ::%d\n", PAGE(page)->capacity, BLOCK(block)->size);
	return (block);
}