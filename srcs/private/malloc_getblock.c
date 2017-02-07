/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_getblock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:52:48 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:52:49 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

t_lst	*get_freed_block(size_t size, t_lst **page)
{
debug("here\n");
	t_lst *block;

	*page = *get_type(size);
	while (*page)
	{
		if (PAGE(*page)->capacity > size)
		{
			block = PAGE(*page)->block;
			while (block)
			{
				if (BLOCK(block)->is_free && BLOCK(block)->size >= size)
					return (block);
				block = block->next;
			}
		}
		*page = (*page)->next;
	}
	return (0);
}

void	reserve_block(t_lst *page, t_lst *block, size_t size)
{
debug("here\n");
	BLOCK(block)->size = (size);
	BLOCK(block)->is_free = 0;
	BLOCK(block)->time = time(0);
	PAGE(page)->capacity -= BLOCK(block)->size;
}

t_lst	*check_page(size_t size)
{
debug("here\n");
	t_lst	*page;
	size_t	block_size;

	page = *get_type(size);
	block_size = size;
	while (page)
	{
		if (PAGE(page)->capacity > block_size)
			return (page);
		page = page->next;
	}
	return (0);
}

t_lst	*malloc_getblock(size_t size)
{
debug("here\n");
	t_lst	*page;
	t_lst	*block;

	if ((block = get_freed_block(size, &page)))
	{
		;
	}
	else if ((page = add_new_page(size)))
	{
		block = PAGE(page)->block;
	}
	else
	{
		return (0);
	}
	split_block(page, block, size);
	reserve_block(page, block, size);
	return (block);
}
