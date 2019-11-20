/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:01:14 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/20 15:57:30 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

// DEBUG INCLUDE
# include <unistd.h>

# include <sys/mman.h>

// DEFINE
# define OVERHEAD		sizeof(t_block_header)
# define HEADER(addr)	*(addr - OVERHEAD)

// ENUM
typedef enum	{
	FREE,
	MERGE,
	MALLOC,
	MMAP,
	MUNMAP,
	REALLOC
}	e_action;

// STRUCTURES, NEED TO STORE PARENT SOMEWHERE
typedef struct				s_block_header {
	size_t					size;
	char					allocated;
}							t_block_header;

typedef struct				s_free_element {
	struct s_free_element	*prev;
	void					*addr;
	struct s_free_element	*next;
}							t_free_element;

typedef struct				s_history_element {
	e_action				action;
	void					*addr;
	size_t					size;
}							t_history_element;

#endif
