#include "libft.h"
#include "private_malloc.h"

#include <unistd.h>

void ooo(void)
	{
	t_lst *tmp_page = g_malloc.small_list;
	t_lst *block;
	int i;
	int j = 0;

	while (tmp_page)
	{
		i = 0;
		block = PAGE(tmp_page)->block;
		ft_print("PAGE INFO : \n"
				"Size: %d\nCapa: %d\nNext: %d\n",
				PAGE(tmp_page)->size, PAGE(tmp_page)->capacity,
				tmp_page->next != 0);
		while (block)
		{
			ft_print("BLOCK INFO : \n"
					"Size: %d\nFree?:%d\nNext:%d\n",
					BLOCK(block)->size,
					BLOCK(block)->is_free, block->next != 0);
			i++;
			block = block->next;
		}
		ft_fdprint(2, "[%d][%d]\n", j, i);
		tmp_page = tmp_page->next;
		j++;
	}
}

void *malloc(size_t size)
{
	t_lst			*block;

	if (size <= 0 || (!g_malloc.init && malloc_initialize() <= 0))
		return (0);
	if (!(block = malloc_getblock(size)))
		return (0);
	return (BLOCK(block) + sizeof(t_header_block));
}

int		main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}