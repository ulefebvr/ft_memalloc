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
	t_lst *block;

	block = 0;
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
