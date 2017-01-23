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
					"Size: %d\nFree?:%d\nNext:%d\nPage:%d\n Page_size:%d\n",
					BLOCK(block)->size,
					BLOCK(block)->is_free, block->next != 0,
					BLOCK(block)->page != 0,
					PAGE(BLOCK(block)->page)->size
					);
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
	return ((void *)BLOCK(block) + sizeof(t_header_block));
}


#include "malloc.h"
// int		main(void)
// {
// 	int		i;
// 	char	*addr;

// 	i = 0;
// 	// while (i < 1024)
// 	while (i < 10)
// 	{
// 		addr = (char*)malloc(1024);
// 		addr[0] = 42;
// 		i++;
// 	}
// 	show_alloc_mem();
// 	return (0);
// }

// int		main(void)
// {
// 	int			i;
// 	char		*addr;

// 	i = 0;
// 	while (i < 1024)
// 	{
// 		addr = (char*)malloc(1024);
// 		// ooo();
// 		addr[0] = 42;
// 		free(addr);
// 		i++;
// 	}
// 	show_alloc_mem();
// 	return (0);
// }


#define M1 (1024 * 1024)

void		print(char *s)
{
	write(1, s, strlen(s));
}

int			main(void)
{
	char	*addr1;
	char	*addr3;

	addr1 = (char *)malloc(16 * M1);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char *)realloc(addr1, 128 * M1);
	addr3[127 * M1] = 42;
	print(addr3);
	return (0);
}