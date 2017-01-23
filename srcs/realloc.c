#include "malloc.h"
#include "private_malloc.h"

void *realloc(void *ptr, size_t size)
{
	t_lst *block;

	block = 0;
	if (ptr == 0)
		return (malloc(size));
	else if (size == 0)
	{
		free(ptr);
		return (0);
	}
	block = &(((t_header_block *)(ptr - sizeof(t_header_block)))->list);
	return (internal_realloc(block, size));
}
