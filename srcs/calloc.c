/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 15:59:38 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/07 15:59:59 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "private_malloc.h"

void	*calloc(size_t count, size_t size)
{
debug("here\n");
	void			*ptr;

	ft_fdprint(2, "Calloc called\n");
	ptr = malloc(count * size);
	ft_bzero(ptr, count * size);
	return (ptr);
}
