/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:53:24 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:53:24 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void	*malloc(size_t size)
{
debug("here\n");
	t_lst			*block;

	// return (0);
	ft_fdprint(2, "Malloc called\n");
	if (size <= 0 || (!g_malloc.init && malloc_initialize() <= 0)
		|| THREAD_SAFE_ACTIVATE != 0 || !(block = malloc_getblock(size)))
	{
		THREAD_SAFE_DEACTIVATE;
		return (0);
	}
	THREAD_SAFE_DEACTIVATE;
	ft_fdprint(2, "size       : %d\n"
		"block      : %p\n"
		"page       : %p\n"
		"page size  : %d\n"
		"page capa  : %d\n"
		"pointer    : %p\n\n",
		size, (void *)BLOCK(block), (void *)PAGE(BLOCK(block)->page),
		PAGE(BLOCK(block)->page)->size, PAGE(BLOCK(block)->page)->capacity,
		(void *)BLOCK(block) + sizeof(t_header_block));
	return ((void *)BLOCK(block) + sizeof(t_header_block));
}
