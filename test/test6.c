/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 18:13:49 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/11 18:13:50 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <pthread.h>
#include <string.h>

void		*loop(void *s)
{
	int			i;
	char		*addr;

	(void)s;
	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(128);
		memset(addr, (int)"A", 128);
		addr = realloc(addr, 1024);
		memset(addr, (int)"B", 1024);
		free(addr);
		i++;
	}
	write(1, "o", 1);
	return (0);
}

int			main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_create(&thread1, 0, loop, 0);
	pthread_create(&thread2, 0, loop, 0);
	pthread_join(thread1, 0);
	pthread_join(thread2, 0);
}