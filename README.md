# ft_memalloc

42born2code school project consisting in creating a thread-safe dynamic memory allocator library.

----------

Compile the library
-------------

Use `make` command to compile the library. To overload the system memory-allocator you have to set these environment variables.

```shell
if [ "$(uname)" == "Linux" ]; then
	export LD_LIBRARY_PATH=$(dirname $(readlink -f path_to_depo/libft_malloc.so))/
else
	export DYLD_LIBRARY_PATH=path_to_depo/
	export DYLD_INSERT_LIBRARIES="path_to_depo/libft_malloc.so"
	export DYLD_FORCE_FLAT_NAMESPACE=1 
fi
```

----------

Library description
-------------

- This memory allocator use the First-Fit method.
- Minimal overhead.

The library includes the following functions:
```c
void	free(void *ptr);
void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	*reallocf(void *ptr, size_t size);

void	show_alloc_mem(void);
```
`show_alloc_mem` show the allocated memory status.

----------

Tests
-------
You can use the `test/test.py` to test the library.
```
$> ./test.py

#####Test malloc
Page reclaims for test0 (NO MALLOC, initial PR):     251
Page reclaims for test1 (WITH MALLOC, PR Full Load): 517
Page reclaims for test2:                             251

For test1 (minus test0 for compensation) the PR is:  266 --> Score (out of 5):

5/5
entre 255 et 272 pages, le malloc fonctionne et l'overhead est raisonnable

#####Test free
Page reclaims for test0 (NO MALLOC, initial PR):     251
Page reclaims for test2:                             251
delta PR between test2 and test0:                    0
Max 3 page reclaim more than test0. The free is working as expected !

#####Test realloc
OK
#####Test realloc++
OK
#####Test errors
OK
```