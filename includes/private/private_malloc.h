/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_malloc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:53:57 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:53:57 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_MALLOC_H
# define PRIVATE_MALLOC_H

# include <pthread.h>
# include <sys/mman.h>

# include "private_datastruct.h"
# include "private_macro.h"
# include "private_functions.h"

t_malloc							g_malloc;
pthread_mutex_t						g_malloc_lock;

#endif
