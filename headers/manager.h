/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:01:14 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/26 20:12:52 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

# include <sys/mman.h>
# include "libft.h"

// DEFINE
# define OVERHEAD		sizeof(t_block_header)
# define HEADER(addr)	*(addr - OVERHEAD)
// 64bits
//# define TINY 992
//# define SMALL 15360
//# define LARGE ?????

//32 bits
# define TINY 10//496
# define SMALL 20//15359
# define LARGE 40//?????

// STRUCTURES
typedef struct				s_block_header {
	size_t					size;
	char					allocated;
}							t_block_header;

typedef struct				s_free_element {
	struct s_free_element	*prev;
	void					*addr;
	struct s_free_element	*next;
}							t_free_element;

typedef struct				s_mapped_element {
	void					*addr;
	size_t					size;
	struct s_mapped_element	*next;
}							t_mapped_element;

typedef struct				s_manager {
	t_free_element			*bin[4]; //           [0-TINY, 1-SMALL, 2-LARGE, 3-HUGE]
	t_mapped_element		*mapped_memory[4]; // [0-TINY, 1-SMALL, 2-LARGE, 3-HUGE]
}							t_manager;

extern t_manager			*g_manager;
void						show_alloc_mem();

#endif
