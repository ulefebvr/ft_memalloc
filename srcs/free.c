/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:53:21 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:53:22 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void	free(void *ptr)
{
	t_lst	*block;

	if (ptr == 0 || (block = check_adress(ptr)) == 0)
		return ;
	THREAD_SAFE_ACTIVATE;
	BLOCK(block)->is_free = 1;
	PAGE(BLOCK(block)->page)->capacity += BLOCK(block)->size;
	if (block_size(BLOCK(block)->size) != TINY_MAX_ALLOC
		&& block_size(BLOCK(block)->size) != SMALL_MAX_ALLOC)
	{
		free_large_page(block);
	}
	else
	{
		apply_buddy_check(block);
		free_empty_page(block);
	}
	THREAD_SAFE_DEACTIVATE;
}
