/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:32:25 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 11:32:25 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

void		free(void *ptr)
{
	t_header_page	*page;
	t_header_block	*block;

	page = 0;
	block = 0;
	if (ptr == 0 || (!(page = check_ptr_page(ptr))
		&& !(block = check_ptr_block(page, ptr))))
		{
		return ;
		}
	internal_free(page, block);
}
