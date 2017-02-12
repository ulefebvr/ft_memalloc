#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <mcheck.h>

#include <stdio.h>

int main(void)
{
	mtrace();
	void * ptr = malloc(1024);

	printf("[%p]\n", ptr);

	ptr = realloc(ptr, 2048);
	ptr = realloc(ptr, 2);
	free(ptr);
	muntrace();
}