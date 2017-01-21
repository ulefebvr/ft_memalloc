#include "libft.h"
#include "private_malloc.h"

t_lst *split_block(t_lst *page, t_lst *block, size_t size)
{
	t_header_block *next;

	if (PAGE(page)->capacity >= ((size) + sizeof(t_header_block) * 2))
	{
		next = (void *)BLOCK(block) + sizeof(t_header_block) + size;
		ft_bzero(next, sizeof(t_header_block));
		block->next = &next->list;
		next->list.prev = block;
		next->is_free = 1;
		next->page = page;
		PAGE(page)->capacity -= sizeof(t_header_block);
		next->size = PAGE(page)->capacity - size;
	}
	return (block);
}

void join_block(t_lst *b1, t_lst *b2)
{
	b1->size = b2->size + sizeof(t_header_block);
	b1->next = b2->next;
	if (b2->next) b2->next->prev = b1;
	b1->is_free = 1;
}