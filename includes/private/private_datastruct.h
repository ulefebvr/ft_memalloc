/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_datastruct.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:46:00 by ulefebvr          #+#    #+#             */
/*   Updated: 2017/02/12 15:46:00 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_DATASTRUCT_H
# define PRIVATE_DATASTRUCT_H

# include <unistd.h>

typedef enum				e_stype
{
	TINY = 128, SMALL = 1024, LARGE
}							t_stype;

# define CAPA				100

typedef struct				s_header_block
{
	size_t					size;
	size_t					capacity;
	time_t					time;
	void					*ptr;
	struct s_header_block	*next;
}							t_header_block;

typedef t_header_block		t_hb;

typedef struct				s_header_page
{
	int						capacity;
	t_stype					type;
	t_header_block			storage[CAPA];
	void					*ptr;
	t_header_block			*free;
	t_header_block			*reserved;
	struct s_header_page	*next;
}							t_header_page;

typedef t_header_page		t_hp;

typedef struct				s_malloc
{
	int						init;
	t_header_page			*tiny_list;
	t_header_page			*small_list;
	t_header_block			*large_list;
}							t_malloc;

#endif
