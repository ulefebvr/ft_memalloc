/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:53:26 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:53:27 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "private_malloc.h"

void	*realloc(void *ptr, size_t size)
{
debug("here\n");
	t_lst *block;

	block = 0;
	ft_fdprint(2, "Realloc called on %p , %d\n", ptr, size);	
	if (ptr == 0)
		return (malloc(size));
	else if ((block = check_adress(ptr)) == 0)
		return (0);
	else if (size == 0)
	{
		free(ptr);
		return (0);
	}
	return (internal_realloc(block, size));
}

void *reallocf(void *ptr, size_t size)
{
debug("here\n");
	ft_fdprint(2, "Reallocf called\n");
	return (realloc(ptr, size));
}