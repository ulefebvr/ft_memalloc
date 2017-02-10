/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:53:16 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 11:32:18 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

#include <unistd.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		*((char*)s + counter) = '\0';
		counter++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		((char*)dest)[counter] = ((char*)src)[counter];
		counter++;
	}
	return (dest);
}

int		check_init(void)
{
	if (!g_malloc.init)
	{
		if (pthread_mutex_init(&g_malloc_lock, 0))
			return (0);
		g_malloc.init = 1;
	}
	return (1);
}
