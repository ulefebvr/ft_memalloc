#include "private_malloc.h"

static void				free_large_block(t_header_block *block)
{
	t_header_block		*b_block;

	if ((b_block = g_malloc.large_list) == block)
		g_malloc.large_list = block->next;
	else
	{
		while (b_block && b_block->next != block)
			b_block = b_block->next;
		b_block->next = block->next;
	}
	munmap((void *)block, block->capacity);
}

static t_header_block	*the_block_before(
	t_header_page *page, t_header_block *block)
{
	t_header_block		*b_block;

	if ((void *)block == (void *)(b_block = page->reserved))
		return (0);
	while (b_block && b_block->next != block)
		b_block = b_block->next;
	return (b_block);
}

static void				free_page(t_header_page *page)
{
	t_header_page		*b_page;

	b_page = page->type == TINY ? g_malloc.tiny_list : g_malloc.small_list;
	if (b_page == page && page->type == TINY)
		g_malloc.tiny_list = page->next;
	else if (b_page == page && page->type == SMALL)
		g_malloc.small_list = page->next;
	else
	{
		while (b_page && b_page->next != page)
			b_page = b_page->next;
		b_page->next = page->next;
	}
	munmap((void *)page->ptr, CAPA * page->type);
	munmap((void *)page, S_HPAGE);
}

static int				count_page(t_stype type)
{
	int					count;
	t_header_page		*tmp_page;

	count = 0;
	tmp_page = type == TINY ? g_malloc.tiny_list : g_malloc.small_list;
	while (++count && tmp_page)
		tmp_page = tmp_page->next;
	return (count);
}

void					internal_free(
	t_header_page *page, t_header_block *block)
{
	t_header_block		*b_block;

	if (!page)
		return (free_large_block(block));
	++page->capacity;
	if ((b_block = the_block_before(page, block)))
		b_block->next = block->next;
	else
		page->reserved = block->next;
	block->next = page->free;
	page->free = block;
	if (count_page(page->type) > 1 && page->capacity == CAPA)
		free_page(page);
}
