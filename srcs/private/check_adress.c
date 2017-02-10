/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_adress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:31:59 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 11:32:00 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

static t_header_page	*check_type(t_header_page *p, void *ptr)
{
	while (p)
	{
		if (p->ptr <= ptr && ptr < p->ptr + PAGE_SIZE_MULTIPLE(CAPA * p->type))
			return (p);
		p = p->next;
	}
	return (0);
}

t_header_page			*check_ptr_page(void *ptr)
{
	t_header_page		*page;

	if ((page = check_type(g_malloc.tiny_list, ptr)))
		return (page);
	page = check_type(g_malloc.small_list, ptr);
	return (page);
}

t_header_block			*check_ptr_block(t_header_page *page, void *ptr)
{
	t_header_block		*block;

	block = (page == 0) ? g_malloc.large_list : page->reserved;
	while (block && block->ptr != ptr)
		block = block->next;
	return (block);
}
