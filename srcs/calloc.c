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

#include "malloc.h"
#include "private_malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc((nmemb + 1) * size);
	ft_bzero(ptr, (nmemb + 1) * size);
	return (ptr);
}
