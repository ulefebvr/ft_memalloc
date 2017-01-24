#include "private_malloc.h"

t_lst	*create_new_block(t_lst *page)
{
	t_header_block *block;

	block = (void *)(PAGE(page)) + sizeof(t_header_page);
	block->size = PAGE(page)->capacity;
	block->is_free = 1;
	block->page = page;
	ft_bzero(&block->list, sizeof(t_lst));
	PAGE(page)->capacity -= sizeof(t_header_block);
	return (&block->list);
}

t_lst	*create_new_page(size_t size)
{
	t_header_page	*page;
	size_t			page_lenght;

	page_lenght = page_size(size);
	if (MAP_FAILED == (page = (t_header_page *)MMAP(page_lenght)))
		return (0);
	page->size = page_lenght;
	page->capacity = page_lenght - sizeof(t_header_page);
	page->block = create_new_block(&page->list);
	ft_bzero(&page->list, sizeof(t_lst));
	return (&page->list);
}

void	lst_add_node(t_lst *head, t_lst *node)
{
	if (head && node)
	{
		while (head->next)
			head = head->next;
		head->next = node;
		node->prev = head;
	}
}

t_lst	*add_new_page(size_t size)
{
	t_lst	*new_page;
	t_lst	**head;

	head = get_type(size);
	if (!(new_page = create_new_page(size)))
		return (0);
	if (!*head)
		*head = new_page;
	else
		lst_add_node(*head, new_page);
	return (new_page);
}
