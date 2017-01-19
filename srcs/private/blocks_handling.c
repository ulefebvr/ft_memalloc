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
		PAGE(page)->capacity -= sizeof(t_header_block);
		next->size = PAGE(page)->capacity - size;
	}
	return (block);
}