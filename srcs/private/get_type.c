#include "private_malloc.h"

t_stype				get_type(size_t size)
{
	if (size <= TINY_MAX_ALLOC)
		return (TINY);
	else if (size <= SMALL_MAX_ALLOC)
		return (SMALL);
	return (LARGE);
}
