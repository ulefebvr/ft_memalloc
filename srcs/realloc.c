#include "malloc.h"
#include "private_malloc.h"

void *realloc(void *ptr, size_t size)
{
	t_lst *block;

	block = 0;
	if (ptr == 0)
		return (malloc(size));
	else if ((block = check_adress(ptr)) == 0)
		return (0);
	else if (size == 0)
	{
		free(ptr);
		return (0);
	}
	return (internal_realloc(block, size));
}
