/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:32:22 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 11:32:22 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void	*calloc_without_thread(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc_without_thread((nmemb + 1) * size);
	ft_bzero(ptr, (nmemb + 1) * size);
	return (ptr);
}

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!check_init())
		return (0);
	pthread_mutex_lock(&g_malloc_lock);
	ptr = calloc_without_thread(nmemb, size);
	pthread_mutex_unlock(&g_malloc_lock);
	return (ptr);
}
