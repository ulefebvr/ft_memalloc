/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:27:08 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 16:27:09 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

static void		free_pages(t_header_page *pages)
{
	if (pages->next)
		free_pages(pages->next);
	munmap((void *)pages->ptr, CAPA * pages->type);
	munmap((void *)pages, S_HPAGE);
}

static void		free_large_blocks(t_header_block *blocks)
{
	if (blocks->next)
		free_large_blocks(blocks->next);
	munmap((void *)blocks, blocks->capacity);
}

void			empty_garbage(void)
{
	pthread_mutex_lock(&g_malloc_lock);
	free_pages(g_malloc.tiny_list);
	free_pages(g_malloc.small_list);
	free_large_blocks(g_malloc.large_list);
	ft_bzero(&g_malloc, sizeof(t_malloc));
	pthread_mutex_unlock(&g_malloc_lock);
	pthread_mutex_destroy(&g_malloc_lock);
}
