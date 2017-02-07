/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddy_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:52:28 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:52:30 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void	apply_buddy_check(t_lst *block)
{
debug("here\n");
	if (block->next && BLOCK(block->next)->is_free)
		join_block(block, block->next);
	else if (block->prev && BLOCK(block->prev)->is_free)
		join_block(block->prev, block);
}
