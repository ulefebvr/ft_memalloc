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
	t_lst			*block;

	THREAD_SAFE_ACTIVATE;
	if (size <= 0 || (!g_malloc.init && malloc_initialize() <= 0)
		|| !(block = malloc_getblock(size)))
	{
		THREAD_SAFE_DEACTIVATE;
		return (0);
	}
	THREAD_SAFE_DEACTIVATE;
	return ((void *)BLOCK(block) + sizeof(t_header_block));
}
