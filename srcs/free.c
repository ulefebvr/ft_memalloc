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
debug("here\n");
	t_lst	*block;

	ft_fdprint(2, "Free called on %p", ptr);
	if (ptr == 0 || (block = check_adress(ptr)) == 0)
	{
		ft_fdprint(2, " but no matching\n\n");
		return ;
	}
	ft_fdprint(2, "\n"
		"size       : %d\n"
		"block      : %p\n"
		"page       : %p\n"
		"page size  : %d\n"
		"pointer    : %p\n",
		BLOCK(block)->size, (void *)BLOCK(block), (void *)PAGE(BLOCK(block)->page),
		PAGE(BLOCK(block)->page)->size, ptr);
	// THREAD_SAFE_ACTIVATE;
	// BLOCK(block)->is_free = 1;
	// PAGE(BLOCK(block)->page)->capacity += BLOCK(block)->size;
	// if (block_size(BLOCK(block)->size) != TINY_MAX_ALLOC
	// 	&& block_size(BLOCK(block)->size) != SMALL_MAX_ALLOC)
	// {
	// 	free_large_page(block);
	// }
	// else
	// {
	// 	apply_buddy_check(block);
	// 	free_empty_page(block);
	// }
	ft_fdprint(2, "Success\n\n");
	// THREAD_SAFE_DEACTIVATE;
}
