/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:46:31 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/12 15:46:31 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_FUNCTIONS_H
# define PRIVATE_FUNCTIONS_H

# include "private_datastruct.h"

void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_fdprint(int fd, const char *fmt, ...);
int					check_init(void);

t_stype				get_type(size_t size);
t_header_page		*check_ptr_page(void *ptr);
t_header_block		*check_ptr_block(t_header_page *a, void *b);

void				*reallocf_without_thread(void *a, size_t b);
void				*calloc_without_thread(size_t a, size_t b);
void				free_without_thread(void *ptr);
void				*malloc_without_thread(size_t size);
void				*realloc_without_thread(void *a, size_t b);

void				internal_free(t_header_page *a, t_hb *b);
void				*internal_malloc(size_t size);
void				*internal_realloc(t_hp *a, t_hb *b, void *c, size_t d);

#endif
