#include "libft.h"
#include "private_malloc.h"

t_lst *lst_get_head(t_lst *list)
{
	t_lst *head;

	head = list;
	while (head && head->prev)
	{
		head = head->prev;
	}
	return (head);
}
