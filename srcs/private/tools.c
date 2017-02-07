/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:53:16 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:53:16 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "private_malloc.h"
void	ft_bzero(void *s, size_t n)
{
debug("here\n");
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
debug("here\n");
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		((char*)dest)[counter] = ((char*)src)[counter];
		counter++;
	}
	return (dest);
}
