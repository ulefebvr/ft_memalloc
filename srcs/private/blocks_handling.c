/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:52:24 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:52:25 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

t_lst	*split_block(t_lst *page, t_lst *block, size_t size)
{
debug("here\n");
	t_header_block *next;

	if (BLOCK(block)->size >= ((size) + sizeof(t_header_block)))
	{
		next = (void *)((char *)BLOCK(block) + sizeof(t_header_block) + size);
		ft_bzero(next, sizeof(t_header_block));
		block->next = &next->list;
		next->list.prev = block;
		next->is_free = 1;
		next->page = page;
		PAGE(page)->capacity -= sizeof(t_header_block);
		next->size = PAGE(page)->capacity - size;
	}
	return (block);
}

void	join_block(t_lst *b1, t_lst *b2)
{
debug("here\n");
	BLOCK(b1)->size = BLOCK(b2)->size + sizeof(t_header_block);
	b1->next = b2->next;
	if (b2->next)
		b2->next->prev = b1;
	BLOCK(b1)->is_free = 1;
}
