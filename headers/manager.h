/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:01:14 by lumenthi          #+#    #+#             */
/*   Updated: 2022/07/25 11:25:39 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

# include <sys/mman.h>
# include <unistd.h>
# include "libft.h"

# define CHUNK_OVERHEAD			sizeof(t_chunk) // 24
# define PAGE_OVERHEAD			sizeof(t_page) // 24
# define ALIGNMENT				16

# define CHUNK_PAYLOAD(addr)	addr+CHUNK_OVERHEAD
# define CHUNK_HEADER(addr)		addr-CHUNK_OVERHEAD

# define TINY_P			0
# define SMALL_P		1
# define LARGE_P		2

# define TINY (size_t)(4 * getpagesize())
# define SMALL (size_t)(16 * getpagesize())

typedef struct				s_chunk {
	struct s_chunk			*prev;
	size_t					size;
	struct s_chunk			*next;
}							t_chunk;

typedef struct				s_page {
	size_t					size;
	t_chunk					*malloc_list;
	t_chunk					*free_list;
	struct s_page			*next;
}							t_page;

// malloc.c
extern t_page				*g_page[3]; // [0- TINY, 1- SMALL, 2- LARGE]
t_chunk						*alloc(t_page **page, t_chunk *free_chunk, size_t size);
void						*malloc(size_t size);

// calloc.c
void						*calloc(size_t nelem, size_t size);

// realloc.c
void						*realloc(void *ptr, size_t size);

// free.c
void						free(void *ptr);

// tools.c
void						*page_head(t_chunk *chunk);
int							get_zone(size_t size);
size_t						zone_size(int zone);
void						*ft_alloc(size_t size);
void						ft_free(t_page *page);

// search.c
void						*find_free(size_t size, int begin_zone);
t_page						*valid_address(void *ptr);

// list.c
void						add_page_to_list(t_page **list, t_page *page);
void						remove_page_from_list(t_page **list, t_page *page);
void						add_chunk_to_list(t_chunk **list, t_chunk *chunk);
void						remove_chunk_from_list(t_chunk **list, t_chunk *chunk);
void						merge_chunk(t_chunk **list, t_chunk *chunk);

// show_alloc_mem.c

void						show_alloc_mem();
void						show_free_mem();

#endif
