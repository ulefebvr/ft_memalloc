/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:32:25 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 11:32:25 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void		free_without_thread(void *ptr)
{
	t_header_page	*page;
	t_header_block	*block;

	if (ptr == 0)
		return ;
	page = check_ptr_page(ptr);
	if ((block = check_ptr_block(page, ptr)))
		internal_free(page, block);
}

void		free(void *ptr)
{
	pthread_mutex_lock(&g_malloc_lock);
	free_without_thread(ptr);
	pthread_mutex_unlock(&g_malloc_lock);
}
