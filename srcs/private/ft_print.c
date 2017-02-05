/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 11:26:21 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/30 12:14:54 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

#include <stdarg.h>
#include <unistd.h>

void	print_adress(int base, unsigned long i, int fd)
{
	if (i < (unsigned long)base)
		write(fd, &HEX_STRING[i], 1);
	else
	{
		print_adress(base, i / base, fd);
		write(fd, &HEX_STRING[i % base], 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0 && write(fd, "-", 1))
		n = (~n) + 1;
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		write(fd, &HEX_STRING[n], 1);
}

void	ft_putstr_fd(char const *s, int fd)
{
	char *tmp;

	tmp = (char *)s;
	if (s)
	{
		while (*tmp)
			tmp++;
		write(fd, s, tmp - s);
	}
}

void	run_print(int fd, const char *fmt, va_list list)
{
	while (*fmt)
	{
		if (*fmt == '%' && fmt++)
		{
			if (*fmt == 's')
				ft_putstr_fd(va_arg(list, char *), fd);
			else if (*fmt == 'd')
				ft_putnbr_fd(va_arg(list, int), fd);
			else if (*fmt == 'p')
				print_adress(16, va_arg(list, unsigned long), fd);
			fmt++;
		}
		else
			write(fd, fmt++, 1);
	}
}

int		ft_fdprint(int fd, const char *fmt, ...)
{
	va_list		list;

	if (fmt)
	{
		va_start(list, fmt);
		run_print(fd, fmt, list);
		va_end(list);
	}
	return (1);
}
