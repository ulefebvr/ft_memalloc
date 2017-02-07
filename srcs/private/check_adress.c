/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_adress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:52:33 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:52:33 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

t_lst	*found_block(t_lst *page, void *ptr)
{
debug("%s\n", page == 0 ? "no page" : "page exist");
	t_lst *block;

	block = page == 0 ? 0 : PAGE(page)->block;
	while (block)
	{
		debug("Block exist: [%d]\n", block != 0);
		if ((void *)((char *)BLOCK(block) + sizeof(t_header_block)) == ptr)
		{
			debug("IN 1: [%d]\n", block != 0);
			if (!BLOCK(block)->is_free)
			{
				debug("IN 2: [%d]\n", block != 0);
				// ft_fdprint(2, "%p :::: %p\n", (void *)BLOCK(block) + sizeof(t_header_block), ptr);
				return (block);
			}
		}
		debug("see next block: ");
		block = block->next;
		debug("done\n");
	}
	debug("fail\n");
	// ft_fdprint(2, "[[%d]]\n", block == 0 ? 0 : 1);
	return (0);
}

t_lst	*found_page(t_lst *pages, void *ptr)
{
debug("here\n");
	while (pages)
	{
		if ((void *)((char *)PAGE(pages) + sizeof(t_header_page)) < ptr
			&& ptr < (void *)((char *)PAGE(pages) + PAGE(pages)->size))
			return (pages);
		pages = pages->next;
	}
	return (0);
}

t_lst	*check_adress(void *ptr)
{
debug("here\n");
	t_lst *block;

	block = 0;
	if ((block = found_block(found_page(g_malloc.tiny_list, ptr), ptr)))
		return (block);
	else if ((block = found_block(found_page(g_malloc.small_list, ptr), ptr)))
		return (block);
	return (found_block(found_page(g_malloc.large_list, ptr), ptr));
}
