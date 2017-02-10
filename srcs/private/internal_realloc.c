/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_realloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:32:15 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 11:32:15 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void			*internal_realloc(
	t_header_page *page, t_header_block *block, void *ptr, size_t size)
{
	void		*tmp;

	if (page && get_type(size) == get_type(page->type))
	{
		block->size = size;
		return (ptr);
	}
	else if ((tmp = malloc_without_thread(size)))
	{
		ft_memcpy(tmp, block->ptr, block->size < size ? block->size : size);
		free_without_thread(block->ptr);
		return (tmp);
	}
	return (ptr);
}
