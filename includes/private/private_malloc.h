#ifndef PRIVATE_MALLOC_H
# define PRIVATE_MALLOC_H

# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/mman.h>
# include <stdio.h>

typedef unsigned long long int		t_ulli;

typedef struct						s_lst
{
	struct s_lst					*next;
	struct s_lst					*prev;
}									t_lst;

typedef struct						s_header_page
{
	size_t							size;
	size_t							capacity;
	t_lst							list;
	t_lst							*block;
}									t_header_page;

typedef struct						s_header_block
{
	size_t							size;
	t_lst							list;
	t_lst							*page;
	int								is_free;
}									t_header_block;

typedef struct						s_malloc
{
	int								init;
	t_lst							*tiny_list;
	t_lst							*small_list;
	t_lst							*large_list;
}									t_malloc;

t_malloc							g_malloc;
pthread_mutex_t						g_malloc_lock;

# define PAGE_SIZE					((size_t)sysconf(_SC_PAGESIZE))
# define PS							PAGE_SIZE
# define PAGE_SIZE_MULTIPLE(x)		((((x) + PS - 1) / PS) * PS)

# define TINY_PAGE_SIZE				(2 * PAGE_SIZE)
# define TINY_MAX_ALLOC				128

# define SMALL_PAGE_SIZE			(16 * PAGE_SIZE)
# define SMALL_MAX_ALLOC			1024

# define MMAP_PROT					(PROT_READ | PROT_WRITE)
# define MMAP_FLAG					(MAP_PRIVATE | MAP_ANON)
# define MMAP(size)					mmap(0, size, MMAP_PROT, MMAP_FLAG, -1, 0)

# define OFFSETOF(TYPE, MEMBER)		((size_t) &((TYPE *)0)->MEMBER)
# define CONTAINEROF(ptr, t, m)		((t *)((char *)(ptr) - OFFSETOF(t, m)))

# define BLOCK(x)					(CONTAINEROF(x, t_header_block, list))
# define PAGE(x)					(CONTAINEROF(x, t_header_page, list))

int				malloc_initialize(void);

t_lst			**get_type(size_t size);
size_t			page_size(size_t size);
size_t			block_size(size_t size);

t_lst			*split_block(t_lst *page, t_lst *block, size_t size);
void			join_block(t_lst *b1, t_lst *b2);
void			apply_buddy_check(t_lst *block);

t_lst			*add_new_page(size_t size);

t_lst			*malloc_getblock(size_t size);

t_lst			*check_adress(void *ptr);

void			*internal_realloc(t_lst *block, size_t size);

#endif