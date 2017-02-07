/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:52:36 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:52:36 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void		free_large_page(t_lst *block)
{
debug("here\n");
	t_lst		*page;
	size_t		size;

	page = BLOCK(block)->page;
	size = PAGE(BLOCK(block)->page)->size;
	if (!page->prev)
		*get_type(BLOCK(block)->size) = page->next;
	else
		page->prev->next = page->next;
	if (page->next)
		page->next->prev = page->prev;
	munmap((void *)page, size);
}

static int	page_empty(t_lst *page)
{
debug("here\n");
	return (PAGE(page)->block && PAGE(page)->block->next == 0);
}

void		free_empty_page(t_lst *block)
{
debug("here\n");
	t_lst *page;

	page = BLOCK(block)->page;
	if (page_empty(page) && (void *)PAGE(BLOCK(block)->page)
		!= (void *)*get_type(BLOCK(block)->size))
	{
		if (!page->prev)
			*get_type(BLOCK(block)->size) = page->next;
		else
			page->prev->next = page->next;
		if (page->next)
			page->next->prev = page->prev;
		munmap((void *)PAGE(BLOCK(block)->page), PAGE(BLOCK(block))->size);
	}
}
