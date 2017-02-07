/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_realloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:52:42 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:52:43 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "private_malloc.h"

void	add_block(t_lst *block, size_t size)
{
debug("here\n");
	t_header_block	*new;

	if (block->next && BLOCK(block->next)->is_free)
	{
		ft_memcpy((void *)((char *)BLOCK(block) + size),
			BLOCK(block->next), sizeof(t_header_block));
		block->next = (void *)((char *)BLOCK(block) + size);
		BLOCK(block->next)->size =
			BLOCK(block)->size - size - sizeof(t_header_block);
	}
	else
	{
		new = (void *)((char *)BLOCK(block) + size);
		new->size = BLOCK(block)->size - sizeof(t_header_block);
		PAGE(BLOCK(block)->page)->capacity -= sizeof(t_header_block);
		new->is_free = 1;
		new->list.next = block->next;
		new->list.prev = block;
		new->page = BLOCK(block)->page;
		block->next = &new->list;
	}
}

void	*change_block_size(t_lst *block, size_t size)
{
debug("here\n");
	if (BLOCK(block)->size == size)
		return ((void *)((char *)BLOCK(block) + sizeof(t_header_block)));
	else if (BLOCK(block)->size - size > sizeof(t_header_block))
	{
		add_block(block, size);
		BLOCK(block)->size = size;
		PAGE(BLOCK(block)->page)->capacity += size;
		return ((void *)((char *)BLOCK(block) + sizeof(t_header_block)));
	}
	else if (BLOCK(block)->size < size
		&& block->next && BLOCK(block->next)->is_free
		&& BLOCK(block)->size + BLOCK(block->next)->size - size >
			sizeof(t_header_block))
	{
		BLOCK(block)->size += BLOCK(block->next)->size + sizeof(t_header_block);
		PAGE(BLOCK(block)->page)->capacity += sizeof(t_header_block);
		if ((block->next = block->next->next))
			block->next->prev = block;
		split_block(BLOCK(block)->page, block, size);
		return ((void *)((char *)BLOCK(block) + sizeof(t_header_block)));
	}
	return (NULL);
}

void	*internal_realloc(t_lst *block, size_t size)
{
debug("here\n");
	void *ptr;

	ptr = 0;
	THREAD_SAFE_ACTIVATE;
	if (block_size(size) == block_size(BLOCK(block)->size)
		&& (ptr = change_block_size(block, size)))
	{
		((t_header_block *)(ptr - sizeof(t_header_block)))->time = time(0);
		THREAD_SAFE_DEACTIVATE;
	}
	else if (!THREAD_SAFE_DEACTIVATE && (ptr = malloc(size)))
	{
		ft_memcpy(ptr, (void *)((char *)BLOCK(block) + sizeof(t_header_block)),
			BLOCK(block)->size);
		free((void *)((char *)BLOCK(block) + sizeof(t_header_block)));
		((t_header_block *)(ptr - sizeof(t_header_block)))->time = time(0);
	}
	else
	{
		ptr = (void *)BLOCK(block) + sizeof(t_header_block);
	}
	ft_fdprint(2,
		"size       : %d\n"
		"block      : %p\n"
		"block size : %p\n"
		"page       : %p\n"
		"page size  : %d\n"
		"pointer    : %p\n\n",
		size, ptr - sizeof(t_header_block), (((t_header_block *)(ptr - sizeof(t_header_block)))->size),
		(void *)PAGE(((t_header_block *)(ptr - sizeof(t_header_block)))->page),
		PAGE(((t_header_block *)(ptr - sizeof(t_header_block)))->page)->size,
		ptr);
	return (ptr);
}
