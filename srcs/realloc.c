/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:32:34 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 11:32:35 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void		*realloc_without_thread(void *ptr, size_t size)
{
	t_header_page	*page;
	t_header_block	*block;

	if (ptr == 0)
		return (malloc_without_thread(size));
	page = check_ptr_page(ptr);
	if (size == 0 || !(block = check_ptr_block(page, ptr)))
	{
		if (size == 0)
			free_without_thread(ptr);
		return (0);
	}
	return (internal_realloc(page, block, ptr, size));
}

void		*realloc(void *ptr, size_t size)
{
	void		*ret;

	pthread_mutex_lock(&g_malloc_lock);
	ret = realloc_without_thread(ptr, size);
	pthread_mutex_unlock(&g_malloc_lock);
	return (ret);
}
