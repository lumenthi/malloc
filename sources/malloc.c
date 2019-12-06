/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:00:19 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/06 02:58:16 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

t_page			*g_page[3] = {NULL, NULL, NULL};

void			secure_chunk(t_chunk *chunk) {
	// debug_address((void*)chunk - 1, "SECURING");
	// debug_address(chunk, "CHUNK");
	// debug_address((void*)chunk + CHUNK_OVERHEAD + 1, "SECURING");
	ft_memset((void*)chunk - 1, '\0', 1);
	ft_memset((void*)chunk + CHUNK_OVERHEAD + 1, '\0', 1);
}

t_chunk			*alloc(t_page **page, t_chunk *free_chunk, size_t size) {
	t_chunk **malloc_list = &(*page)->malloc_list;
	t_chunk **free_list = &(*page)->free_list;
	int remaining = 0;
	t_chunk *new_chunk = NULL;
	// REMOVE FROM FREE_LIST
	remove_chunk_from_list(free_list, free_chunk);
	// SPLIT
	remaining = free_chunk->size - size;
	if (remaining > (int)CHUNK_OVERHEAD + SECURE_PADDING * 2) {
		new_chunk = (void*)free_chunk + size;
		new_chunk->prev = NULL;
		new_chunk->size = remaining;
		new_chunk->next = NULL;
		secure_chunk(new_chunk);
		add_chunk_to_list(free_list, new_chunk);
	}
	free_chunk->size = size;
	// SECURE_PADDING
	secure_chunk(free_chunk);
	// ADD TO MALLOC_LIST
	add_chunk_to_list(malloc_list, free_chunk);
	return free_chunk;
}

static t_chunk	*increase_heap(int zone, size_t size) {
	t_page *new_page = NULL;
	t_chunk *new_chunk = NULL;
	size_t alloc_size = 0;

	if (zone == 2)
		alloc_size = size;
	else
		alloc_size = zone_size(zone);
	// PAGE
	new_page = ft_alloc(PAGE_OVERHEAD + alloc_size + SECURE_PADDING * 2);
	new_page++;
	// SECURE_PADDING
	ft_memset((void*)new_page - 1, '\0', 1);
	ft_memset((void*)new_page + PAGE_OVERHEAD + 1, '\0', 1);
	new_page->malloc_list = NULL;
	new_page->free_list = NULL;
	new_page->next = NULL;
	// CHUNK
	new_chunk = (t_chunk *)((void *)new_page + PAGE_OVERHEAD + SECURE_PADDING * 2);

	new_chunk->prev = NULL;
	new_chunk->size = alloc_size;
	new_chunk->next = NULL;
	// LISTS
	add_chunk_to_list(&new_page->free_list, new_chunk);
	alloc(&new_page, new_chunk, size);
	add_page_to_list(zone, new_page);
	return new_chunk;
}

void			*malloc(size_t size) {
	if (debug) {
		ft_putstr("malloc(");
		ft_putnbr(size);
		ft_putstr(");");
	}
	size += SECURE_PADDING + CHUNK_OVERHEAD + SECURE_PADDING;
	int zone = get_zone(size);
	void *ret = find_free(size, zone);
	if (!ret)
		ret = increase_heap(zone, size);
	if (debug) {
		ft_putstr("\nreturn ");
		ft_putaddress(CHUNK_PAYLOAD(ret));
		ft_putstr(";\n");
	}
	// show_alloc_mem();
	// show_free_mem();
	return CHUNK_PAYLOAD(ret);
}
