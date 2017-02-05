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
	t_lst *block;

	block = page == 0 ? 0 : PAGE(page)->block;
	while (block)
	{
		if ((void *)BLOCK(block) + sizeof(t_header_block) == ptr
			&& !BLOCK(block)->is_free)
			return (block);
		block = block->next;
	}
	return (0);
}

t_lst	*found_page(t_lst *pages, void *ptr)
{
	while (pages)
	{
		if ((void *)PAGE(pages) + sizeof(t_header_page) < ptr
			&& ptr < (void *)PAGE(pages) + PAGE(pages)->size)
			return (pages);
		pages = pages->next;
	}
	return (0);
}

t_lst	*check_adress(void *ptr)
{
	t_lst *block;

	block = 0;
	if ((block = found_block(found_page(g_malloc.tiny_list, ptr), ptr)))
		return (block);
	else if ((block = found_block(found_page(g_malloc.small_list, ptr), ptr)))
		return (block);
	return (found_block(found_page(g_malloc.large_list, ptr), ptr));
}
