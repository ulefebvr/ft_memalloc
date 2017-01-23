#include "private_malloc.h"

void	add_block(t_lst *block, size_t size)
{
	t_header_block	*new;

	if (block->next && BLOCK(block->next)->is_free)
	{
		ft_memcpy((void *)BLOCK(block) + size,
			BLOCK(block->next), sizeof(t_header_block));
		block->next = BLOCK(block) + size;
		BLOCK(block->next)->size = 
			BLOCK(block)->size - size - sizeof(t_header_block);
	}
	else
	{
		new = (void *)BLOCK(block) + size;
		new->size = BLOCK(block)->size - sizeof(t_header_block);
		PAGE(BLOCK(block)->page)->capacity -= sizeof(t_header_block);
		new->is_free = 1;
		new->list.next = BLOCK(block)->next;
		new->list.prev = block;
		new->page = BLOCK(block)->page;
		block->next = new;
	}
}

void	*change_block_size(t_lst *block, size_t size)
{
	if (BLOCK(block)->size == size)
		return (BLOCK(block) + sizeof(t_header_block));
	else if (BLOCK(block)->size - size > sizeof(t_header_block))
	{
		add_block(block, size);
		BLOCK(block)->size = size;
		PAGE(BLOCK(block)->page)->capacity += size;
		return (BLOCK(block) + sizeof(t_header_block));
	}
	else if (BLOCK(block)->size < size
		&& block->next && BLOCK(block->next)->is_free
		&& BLOCK(block)->size + BLOCK(block->next)->size > size)
	{
		BLOCK(block)->size += BLOCK(block->next)->size + sizeof(t_header_block);
		PAGE(BLOCK(block)->page)->capacity += sizeof(t_header_block);
		if ((block->next = block->next->next))
			block->next->prev = block;
		split_block(BLOCK(block)->page, block, size);
		return (BLOCK(block) + sizeof(t_header_block));
	}
	return (NULL);
}

void	*internal_realloc(t_lst *block, size_t size)
{
	void *ptr;

	ptr = 0;
	if (block_size(size) == BLOCK(size)->size
		&& (ptr = change_block_size(block, size)))
	{
		;
	}
	else if ((ptr = malloc(size)))
	{
		memcpy(ptr, BLOCK(block) + sizeof(t_header_block), BLOCK(block)->size);
		free(BLOCK(block) + sizeof(t_header_block));
	}
	else
	{
		ptr = BLOCK(block) + sizeof(t_header_block);
	}
	return (ptr);
}
