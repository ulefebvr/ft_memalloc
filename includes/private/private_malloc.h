#ifndef PRIVATE_MALLOC_H
# define PRIVATE_MALLOC_H

# include <pthread.h>

typedef unsigned long long int		t_ulli;

typedef struct						s_list
{
	struct s_list					*next;
	struct s_list					*prev;
}									t_list;

typedef struct						s_header
{
	t_ulli							size;
	t_ulli							capacity;
	int								free;
	t_list							list;
	void							*ptr;
}									t_header;

typedef struct						s_malloc
{
	int								init;
	t_list							tiny;
	t_list							tiny_free;
	t_list							small;
	t_list							small_free;
	t_list							large;
}									t_malloc;

t_malloc							g_malloc;
pthread_mutex_t						g_malloc_lock;

# define SMALL						64
# define LARGE						1024
# define N							(SMALL - sizeof(t_header))
# define M							(LARGE - sizeof(t_header))
# define PAGE_SIZE					((size_t)sysconf(_SC_PAGESIZE))

# define OFFSETOF(TYPE, MEMBER)		((size_t) &((TYPE *)0)->MEMBER)
# define CONTAINEROF(ptr, t, m)		((t *)((char *)(ptr) - OFFSETOF(t, m)))

#endif