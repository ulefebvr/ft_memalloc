#include "private_malloc.h"

void	show_all_blocks(t_lst *block)
{
	while (block)
	{
		if (!(BLOCK(block)->is_free))
		{
			printf("%p - %p : %ld octets\n",
				(void *)BLOCK(block) + sizeof(t_header_block),
				(void *)BLOCK(block) + BLOCK(block)->size
				+ sizeof(t_header_block), BLOCK(block)->size
			);
		}
		block = block->next;
	}
}

void	show_all_pages(t_lst *pages, char *type)
{
	while (pages)
	{
		printf("%s : %p\n", type, (void *)PAGE(pages) + sizeof(t_header_page));
		show_all_blocks(PAGE(pages)->block);
		pages = pages->next;
	}
}

void	show_alloc_mem(void)
{
	show_all_pages(g_malloc.tiny_list, "TINY");
	show_all_pages(g_malloc.small_list, "SMALL");
	show_all_pages(g_malloc.large_list, "LARGE");
}