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
		block = &PAGE(tmp_page)->block;
		while (block)
		{
			i++;
			block = block->next;
		}
		// ft_fdprint(2, "[%d][%d]\n", j, i);
		tmp_page = tmp_page->next;
		j++;
	}
}

void *malloc(size_t size)
{
	t_lst			*block;

	if (size <= 0 || (!g_malloc.init && malloc_initialize() <= 0))
		return (NULL);
	// pthread_mutex_lock(&g_malloc_lock);
	// ft_fdprint(2, "\nmalloc\n");
	block = malloc_getblock(size);
	// ooo();
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
	// addr = (char *)malloc(1024);
	// addr[i] = 'a';
	// addr[1] = 0;

	// addr = (char *)malloc(1024);
	// addr[0] = 'b';
	// addr[1] = 0;	

	return (0);
}