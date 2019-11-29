/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:01:14 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/29 19:13:51 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

# include <sys/mman.h>
# include "libft.h"

// DEFINE
# define CHUNK_OVERHEAD			sizeof(t_chunk)
# define PAGE_OVERHEAD			sizeof(t_page)

# define CHUNK_HEADER(addr)		*(addr - CHUNK_OVERHEAD)
# define CHUNK_PAYLOAD(addr)	*(addr + CHUNK_OVERHEAD)

# define PAGE_HEADER(addr)		*(addr - PAGE_OVERHEAD)
# define PAGE_PAYLOAD(addr)		*(addr + PAGE_OVERHEAD)

# define TINY_P			0
# define SMALL_P		1
# define LARGE_P		2

// 64bits
//# define TINY 992
//# define SMALL 15360

//32 bits
# define TINY 10//496
# define SMALL 20//15359

typedef struct				s_chunk {
	struct s_chunk			*prev;
	size_t					size;
	struct s_chunk			*next;
}							t_chunk;

typedef struct				s_page {
	t_chunk					*malloc_list;
	t_chunk					*free_list;
	struct s_page			*next;
}							t_page;

extern t_page				*g_page[3]; // [0- TINY, 1- SMALL, 2- LARGE]
void						show_alloc_mem();

#endif
