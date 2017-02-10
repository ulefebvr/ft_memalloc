/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:32:28 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 11:32:30 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void	*malloc_without_thread(size_t size)
{
	if (size <= 0)
		return (0);
	return (internal_malloc(size));
}

void	*malloc(size_t size)
{
	void	*ptr;

	if (!check_init())
		return (0);
	pthread_mutex_lock(&g_malloc_lock);
	ptr = malloc_without_thread(size);
	pthread_mutex_unlock(&g_malloc_lock);
	return (ptr);
}
