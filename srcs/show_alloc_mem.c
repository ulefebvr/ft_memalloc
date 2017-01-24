#include "private_malloc.h"

static void	show_all_blocks(t_lst *block)
{
	while (block)
	{
		if (!(BLOCK(block)->is_free))
		{
			ft_fdprint(1, "%p - %p : %d octets\n",
				(void *)BLOCK(block) + sizeof(t_header_block),
				(void *)BLOCK(block) + BLOCK(block)->size
				+ sizeof(t_header_block), (int)BLOCK(block)->size
			);
		}
		block = block->next;
	}
}

static void	show_all_pages(t_lst *pages, char *type)
{
	(void)type;
	while (pages)
	{
		ft_fdprint(1, "%s : %p\n", type,
			(void *)PAGE(pages) + sizeof(t_header_page));
		show_all_blocks(PAGE(pages)->block);
		pages = pages->next;
	}
}

void		show_alloc_mem(void)
{
	show_all_pages(g_malloc.tiny_list, "TINY");
	show_all_pages(g_malloc.small_list, "SMALL");
	show_all_pages(g_malloc.large_list, "LARGE");
}