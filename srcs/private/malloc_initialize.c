/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_initialize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:52:51 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:52:52 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

#include <pthread.h>

int	malloc_initialize(void)
{
debug("here\n");
	ft_bzero(&g_malloc, sizeof(t_malloc));
	g_malloc.init = 1;
	// pthread_mutex_init(&g_malloc_lock, 0);
	return (g_malloc.init);
}
