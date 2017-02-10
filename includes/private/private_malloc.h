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

# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/mman.h>
# include <stdio.h>
# include <time.h>

typedef unsigned long long int		t_ulli;

typedef enum						e_stype
{
	TINY = 128, SMALL = 1024, LARGE
}									t_stype;

# define CAPA						100

typedef struct						s_header_block
{
	size_t							size;
	size_t							capacity;
	time_t							time;
	void							*ptr;
	struct s_header_block			*next;
}									t_header_block;

typedef t_header_block				t_hb;

typedef struct						s_header_page
{
	int								capacity;
	t_stype							type;
	t_header_block					storage[CAPA];
	void							*ptr;
	t_header_block					*free;
	t_header_block					*reserved;
	struct s_header_page			*next;
}									t_header_page;

typedef t_header_page				t_hp;

typedef struct						s_malloc
{
	int								init;
	t_header_page					*tiny_list;
	t_header_page					*small_list;
	t_header_block					*large_list;
}									t_malloc;

t_malloc							g_malloc;
pthread_mutex_t						g_malloc_lock;

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

void								ft_bzero(void *s, size_t n);
void								*ft_memcpy(
										void *dest, const void *src, size_t n);
int									ft_fdprint(int fd, const char *fmt, ...);

t_stype								get_type(size_t size);
t_header_page						*check_ptr_page(void *ptr);
t_header_block						*check_ptr_block(t_header_page *a, void *b);

void								*reallocf_without_thread(void *a, size_t b);
void								*calloc_without_thread(size_t a, size_t b);
void								free_without_thread(void *ptr);
void								*malloc_without_thread(size_t size);
void								*realloc_without_thread(void *a, size_t b);

void								internal_free(t_header_page *a, t_hb *b);
void								*internal_malloc(size_t size);
void								*internal_realloc(
										t_hp *a, t_hb *b, void *c, size_t d);

#endif
