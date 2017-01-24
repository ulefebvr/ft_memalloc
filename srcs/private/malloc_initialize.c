#include "private_malloc.h"

int malloc_initialize(void)
{
	ft_bzero(&g_malloc, sizeof(t_malloc));
	g_malloc.init = 1;
	return (g_malloc.init);
}
