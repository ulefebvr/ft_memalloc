/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:53:19 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:53:19 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

t_lst	**get_type(size_t size)
{
	if (size <= TINY_MAX_ALLOC)
		return (&g_malloc.tiny_list);
	if (size <= SMALL_MAX_ALLOC)
		return (&g_malloc.small_list);
	return (&g_malloc.large_list);
}

size_t	page_size(size_t size)
{
	if (size <= TINY_MAX_ALLOC)
		return (TINY_PAGE_SIZE);
	if (size <= SMALL_MAX_ALLOC)
		return (SMALL_PAGE_SIZE);
	return (size);
}

size_t	block_size(size_t size)
{
	if (size <= TINY_MAX_ALLOC)
		return (TINY_MAX_ALLOC);
	if (size <= SMALL_MAX_ALLOC)
		return (SMALL_MAX_ALLOC);
	return (size);
}
