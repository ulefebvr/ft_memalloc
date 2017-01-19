#include "private_malloc.h"

t_lst	*create_new_block(t_lst *page)
{
	t_header_block *block;

	block = (void *)(PAGE(page)) + sizeof(t_header_page);
	block->size = 0;
	block->is_free = 1;
	block->list.next = 0;
	block->list.prev = 0;
	return (&block->list);
}

t_lst	*create_new_page(size_t size)
{
	t_header_page	*page;
	size_t			page_lenght;

	page_lenght = page_size(size);
	page = (t_header_page *)MMAP(page_lenght);
	page->size = page_lenght;
	page->capacity = page_lenght - sizeof(t_header_page);
	page->block = *create_new_block(&page->list);
	page->list.next = NULL;
	page->list.prev = NULL;
	return (&page->list);
}

void	lst_add_node(t_lst *head, t_lst *node)
{
	while (head->next)
		head = head->next;
	head->next = node;
	node->prev = head;
}

t_lst	*add_new_page(size_t size)
{
	t_lst	*new_page;
	t_lst	**head;

	head = get_type(size);
	new_page = create_new_page(size);
	if (!*head)
		*head = new_page;
	else
		lst_add_node(*head, new_page);
	return (new_page);
}