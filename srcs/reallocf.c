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

#include "malloc.h"
#include "private_malloc.h"

void		*reallocf(void *ptr, size_t size)
{
	void			*ret;
	t_header_block	*block;

	if (ptr == 0)
		return (malloc(size));
	if (0 == (block = check_ptr_block(check_ptr_page(ptr), ptr)))
		return (0);
	else if (size == 0)
	{
		free(ptr);
		return (0);
	}
	ret = malloc(size);
	ft_memcpy(ret, block->ptr, block->size < size ? block->size : size);
	free(ptr);
	return (ret);
}
