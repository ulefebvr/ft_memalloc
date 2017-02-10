#include "private_malloc.h"

void	*malloc(size_t size)
{
	if (size <= 0)
		return (0);
	return (internal_malloc(size));
}
