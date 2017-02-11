/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:35:31 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 16:35:31 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void	show_all_blocks(t_header_block *block)
{
	while (block)
	{
		ft_fdprint(2, "%p - %p : %d octets\n",
			block->ptr, block->ptr + block->size, block->size);
		block = block->next;
	}
}

void	show_all_pages(t_header_page *pages, char *typename)
{
	if (pages)
		ft_fdprint(2, "%s\n", typename);
	while (pages)
	{
		show_all_blocks(pages->reserved);
		pages = pages->next;
	}
}

void	show_alloc_mem(void)
{
	if (!check_init())
		return ;
	pthread_mutex_lock(&g_malloc_lock);
	show_all_pages(g_malloc.tiny_list, "TINY");
	show_all_pages(g_malloc.small_list, "SMALL");
	if (g_malloc.large_list)
	{
		ft_fdprint(2, "LARGE\n");
		show_all_blocks(g_malloc.large_list);
	}
	pthread_mutex_unlock(&g_malloc_lock);
}
