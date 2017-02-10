/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:08:40 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 16:08:40 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void		*reallocf_without_thread(void *ptr, size_t size)
{
	void			*ret;
	t_header_block	*block;

	if (ptr == 0)
		return (malloc_without_thread(size));
	if (0 == (block = check_ptr_block(check_ptr_page(ptr), ptr)))
		return (0);
	else if (size == 0)
	{
		free_without_thread(ptr);
		return (0);
	}
	ret = malloc_without_thread(size);
	ft_memcpy(ret, block->ptr, block->size < size ? block->size : size);
	free_without_thread(ptr);
	return (ret);
}

void		*reallocf(void *ptr, size_t size)
{
	void	*ret;

	if (!check_init())
		return (0);
	pthread_mutex_lock(&g_malloc_lock);
	ret = reallocf_without_thread(ptr, size);
	pthread_mutex_unlock(&g_malloc_lock);
	return (ret);
}
