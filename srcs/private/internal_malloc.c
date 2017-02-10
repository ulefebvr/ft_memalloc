/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:32:12 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/10 11:32:13 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_malloc.h"

static t_header_block	*found_free_block(t_stype type, t_header_page **page)
{
	*page = (type == TINY) ? g_malloc.tiny_list : g_malloc.small_list;
	while (*page && (*page)->capacity == 0)
	{
		*page = (*page)->next;
	}
	return (*page != 0 ? (*page)->free : 0);
}

static t_header_page	*create_new_page(t_stype type)
{
	int				i;
	void			*ptr;
	t_header_page	*page;

	i = -1;
	if (MAP_FAILED == (void *)(page = MMAP(PAGE_SIZE_MULTIPLE(S_HPAGE)))
		|| MAP_FAILED == (ptr = MMAP(PAGE_SIZE_MULTIPLE(CAPA * type))))
		return (0);
	ft_bzero((void *)page, S_HPAGE);
	page->ptr = ptr;
	page->capacity = CAPA;
	page->type = type;
	while (++i < CAPA)
	{
		page->storage[i].next = (i + 1 < CAPA) ? &(page->storage[i + 1]) : 0;
		page->storage[i].ptr = (char *)page->ptr + (i * type);
	}
	page->free = &(page->storage[0]);
	page->next = (type == TINY) ? g_malloc.tiny_list : g_malloc.small_list;
	if (type == TINY)
		g_malloc.tiny_list = page;
	else
		g_malloc.small_list = page;
	return (page);
}

static void				reserve_block(
	t_header_page *page, t_header_block *block, size_t size)
{
	--page->capacity;
	page->free = block->next;
	block->next = page->reserved;
	page->reserved = block;
	block->size = size;
}

static void				*create_large_block(size_t size)
{
	void				*ptr;
	t_header_block		*block;

	if (MAP_FAILED == (ptr = MMAP(PAGE_SIZE_MULTIPLE(size + S_HBLOCK))))
		return (0);
	block = (t_header_block *)ptr;
	block->next = g_malloc.large_list;
	g_malloc.large_list = block;
	block->ptr = (char *)ptr + S_HBLOCK;
	block->size = size;
	return (block->ptr);
}

void					*internal_malloc(size_t size)
{
	t_header_page	*page;
	t_header_block	*block;
	t_stype			type;

	page = 0;
	if (LARGE == (type = get_type(size)))
		return (create_large_block(size));
	if (!(block = found_free_block(type, &page)))
	{
		if (!(page = create_new_page(type)))
			return (0);
		block = page->free;
	}
	reserve_block(page, block, size);
	return (block->ptr);
}
