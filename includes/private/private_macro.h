/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_macro.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:46:19 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/12 15:46:19 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_MACRO_H
# define PRIVATE_MACRO_H

# define S_HBLOCK					(sizeof(t_header_block))
# define S_HPAGE					(sizeof(t_header_page))

# define PAGE_SIZE					(getpagesize())
# define PS							PAGE_SIZE

# define PAGE_SIZE_MULTIPLE(x)		((((x) + PS - 1) / PS) * PS)
# define PSM(x)						PAGE_SIZE_MULTIPLE(x)

# define TINY_MAX_ALLOC				128
# define SMALL_MAX_ALLOC			1024

# define MMAP_PROT					(PROT_READ | PROT_WRITE)
# define MMAP_FLAG					(MAP_PRIVATE | MAP_ANON)
# define MMAP(size)					mmap(0, size, MMAP_PROT, MMAP_FLAG, -1, 0)

# define HEX_STRING					"0123456789ABCDEF"

# define HIDDEN						(__attribute__((visibility("hidden"))))

#endif
