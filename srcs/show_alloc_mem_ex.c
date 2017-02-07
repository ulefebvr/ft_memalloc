/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:53:29 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:53:29 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

static void	show_all_blocks(t_lst *block)
{
debug("here\n");
	char *tmp_time;

	while (block)
	{
		if (!(BLOCK(block)->is_free))
		{
			tmp_time = ctime(&BLOCK(block)->time);
			tmp_time[24] = 0;
			ft_fdprint(1, "%s %p - %p : %d octets\n",
				tmp_time,
				(void *)((char *)BLOCK(block) + sizeof(t_header_block)),
				(void *)((char *)BLOCK(block) + BLOCK(block)->size)
				+ sizeof(t_header_block), BLOCK(block)->size,
				BLOCK(block)->size);
		}
		block = block->next;
	}
}

static void	show_all_pages(t_lst *pages, char *type)
{
debug("here\n");
	(void)type;
	while (pages)
	{
		ft_fdprint(1, "%s : %p\n", type,
			(void *)((char *)PAGE(pages) + sizeof(t_header_page)));
		show_all_blocks(PAGE(pages)->block);
		pages = pages->next;
	}
}

void		show_alloc_mem_ex(void)
{
debug("here\n");
	show_all_pages(g_malloc.tiny_list, "TINY");
	show_all_pages(g_malloc.small_list, "SMALL");
	show_all_pages(g_malloc.large_list, "LARGE");
}
