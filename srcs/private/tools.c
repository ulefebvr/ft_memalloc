#include <unistd.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		*((char*)s + counter) = '\0';
		counter++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int counter;

	counter = 0;
	while (counter < n)
	{
		((char*)dest)[counter] = ((char*)src)[counter];
		counter++;
	}
	return (dest);
}
