#include "private_malloc.h"

void		free_large_page(t_lst *block)
{
	t_lst *page;

	page = PAGE(BLOCK(block)->page);
	if (!page->prev)
		*get_type(BLOCK(block)->size) = page->next;
	else
		page->prev->next = page->next;
	if (page->next)
		page->next->prev = page->prev;
	munmap((void *)PAGE(BLOCK(block)->page), PAGE(BLOCK(block)->size));
}

static int	page_empty(t_lst *page)
{
	return (BLOCK(PAGE(page)->block)->next == 0);
}

void		free_empty_page(t_lst *block)
{
	t_lst *page;

	page = PAGE(BLOCK(block)->page);
	if (page_empty(page) &&
		PAGE(BLOCK(block)->page) != *get_type(BLOCK(block)->size))
	{
		if (!page->prev)
			*get_type(BLOCK(block)->size) = page->next;
		else
			page->prev->next = page->next;
		if (page->next)
			page->next->prev = page->prev;
		munmap((void *)PAGE(BLOCK(block)->page), PAGE(BLOCK(block)->size));
	}
}
