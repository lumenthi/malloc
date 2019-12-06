/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:01:14 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/06 02:12:43 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

# include <sys/mman.h>
# include "libft.h"

// DEFINE

// DEBUG
# define d ft_putstr(".");
extern int		debug;

# define CHUNK_OVERHEAD			sizeof(t_chunk) // 24
# define PAGE_OVERHEAD			sizeof(t_page) // 24
# define SECURE_PADDING			1

# define CHUNK_PAYLOAD(addr)	addr+CHUNK_OVERHEAD+SECURE_PADDING+1
# define CHUNK_HEADER(addr)		addr-1-SECURE_PADDING-CHUNK_OVERHEAD

# define TINY_P			0
# define SMALL_P		1
# define LARGE_P		2

// 64bits
//# define TINY 992
//# define SMALL 15360

//32 bits
# define TINY 992 + CHUNK_OVERHEAD//496 //124
# define SMALL 15369 + CHUNK_OVERHEAD//15359

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

// malloc.c
extern t_page				*g_page[3]; // [0- TINY, 1- SMALL, 2- LARGE]
t_chunk						*alloc(t_page **page, t_chunk *free_chunk, size_t size);
void						*malloc(size_t size);

// realloc.c
void						*realloc(void *ptr, size_t size);

// free.c
void						free(void *ptr);

// tools.c
// debug functions
void						debug_address(void *address, char *str);
void						debug_size(size_t size, char *name);
//
void						*page_head(t_chunk *chunk);
int							get_zone(size_t size);
size_t						zone_size(int zone);
int							is_valid(void *tmp);
void						*ft_alloc(size_t size);

// search.c
void						*find_free(size_t size, int begin_zone);
int							invalid_address(void *ptr);

// list.c
void						add_page_to_list(int zone, t_page *new_page);
void						add_chunk_to_list(t_chunk **list, t_chunk *chunk);
void						remove_chunk_from_list(t_chunk **list, t_chunk *chunk);

// show_alloc_mem.c

void						show_alloc_mem();
void						show_free_mem();

#endif
