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

	if (size <= 0 || (!g_malloc.init && malloc_initialize() <= 0))
		return (0);
	if (!(block = malloc_getblock(size)))
		return (0);
	return ((void *)BLOCK(block) + sizeof(t_header_block));
}
