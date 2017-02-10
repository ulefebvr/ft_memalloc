/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:53:59 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/05 19:54:00 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

/*
** The malloc(), calloc(), XXXXXXXX, realloc(), and reallocf() functions allo-
** cate memory.  The allocated memory is aligned such that it can be used for
** any data type, including AltiVec- and SSE-related types.  The free() func-
** tion frees allocations that were created via the preceding allocation func-
** tions.
*/

/*
** The malloc() function allocates size bytes of memory and returns a pointer
** to the allocated memory.
*/

void	*malloc(size_t size);

/*
** The calloc() function contiguously allocates enough space for count objects
** that are size bytes of memory each and returns a pointer to the allocated
** memory.  The allocated memory is filled with bytes of value zero.
*/

void	*calloc(size_t count, size_t size);

/*
** The realloc() function tries to change the size of the allocation pointed
** to by ptr to size, and returns ptr.  If there is not enough room to enlarge
** the memory allocation pointed to by ptr, realloc() creates a new alloca-
** tion, copies as much of the old data pointed to by ptr as will fit to the
** new allocation, frees the old allocation, and returns a pointer to the
** allocated memory.  If ptr is NULL, realloc() is identical to a call to
** malloc() for size bytes.  If size is zero and ptr is not NULL, a new, mini-
** mum sized object is allocated and the original object is freed.  When
** extending a region allocated with calloc(3), realloc(3) does not guarantee
** that the additional memory is also zero-filled.
*/

void	*realloc(void *ptr, size_t size);

/*
** The reallocf() function is identical to the realloc() function, except that
** it will free the passed pointer when the requested memory cannot be allo-
** cated.  This is a FreeBSD specific API designed to ease the problems with
** traditional coding styles for realloc causing memory leaks in libraries.
*/

void	*reallocf(void *ptr, size_t size);

/*
** The free() function deallocates the memory allocation pointed to by ptr. If
** ptr is a NULL pointer, no operation is performed.
*/

void	free(void *ptr);

/*
** The show_alloc_mem() and show_alloc_mem_ex() show the status of mapped
** memory.
*/

void	show_alloc_mem(void);
void	show_alloc_mem_ex(void);

#endif
