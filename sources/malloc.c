/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:00:19 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/02 03:20:05 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

t_page	*g_page[3] = {NULL, NULL, NULL};

void	*ft_alloc(size_t size) {
	void *ret;

	ret = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (ret == MAP_FAILED)
		ft_exit("MMAP ERROR, CANT MAP NECESSARY MEMORY, EXITING\n");
	return (ret);
}

int		get_zone(size_t size) {
	if (size > TINY) {
		if (size > SMALL)
			return LARGE_P;
		return SMALL_P;
	}
	return TINY_P;
}

// TODO CODE FIND IN LIST

size_t	zone_size(int zone) {
	if (zone == TINY_P)
		return TINY;
	else
		return SMALL;
}

void	add_page_to_list(int zone, t_page *new_page) {
	t_page	**head = &g_page[zone];
	t_page	*tmp = *head;

	if (*head == NULL) {
		*head = new_page;
		return ;
	}
	if (new_page < *head) {
		new_page->next = *head;
		*head = new_page;
		return ;
	}
	while (tmp->next != NULL && tmp < tmp->next)
		tmp = tmp->next;
	if (tmp->next)
		new_page->next = tmp->next;
	tmp->next = new_page;
}

void	add_chunk_to_list(t_chunk **list, t_chunk *chunk) {
	t_chunk	*tmp = *list;
	if (*list == NULL) {
		chunk->prev = NULL;
		*list = chunk;
		return ;
	}
	if (chunk < *list) {
		chunk->prev = NULL;
		chunk->next = *list;
		(*list)->prev = chunk;
		*list = chunk;
		return ;
	}
	while (tmp->next && chunk > tmp->next)
		tmp = tmp->next;
	if (tmp->next) {
		chunk->next = tmp->next;
		tmp->next->prev = chunk;
	}
	else {
		chunk->next = NULL;
	}
	tmp->next = chunk;
	chunk->prev = tmp;
}

void	remove_chunk_from_list(t_chunk **list, t_chunk *chunk) {
	if (*list == chunk) {
		*list = chunk->next;
		return ;
	}
	if (chunk->next)
		chunk->next->prev = chunk->prev;
	if (chunk->prev)
		chunk->prev->next = chunk->next;
}

t_chunk	*alloc(t_page **page, t_chunk *free_chunk, size_t size) {
	t_chunk **malloc_list = &(*page)->malloc_list;
	t_chunk **free_list = &(*page)->free_list;
	int remaining = 0;
	t_chunk *new_chunk = NULL;
	// REMOVE FROM FREE_LIST
	remove_chunk_from_list(free_list, free_chunk);
	// SPLIT
	remaining = free_chunk->size - size;
	if (remaining > (int)CHUNK_OVERHEAD) {
		new_chunk = (t_chunk *)((size_t)free_chunk + size);
		new_chunk->prev = NULL;
		new_chunk->size = remaining;
		new_chunk->next = NULL;
		add_chunk_to_list(free_list, new_chunk);
	}
	free_chunk->size = size;
	// ADD TO MALLOC_LIST
	add_chunk_to_list(malloc_list, free_chunk);
	return free_chunk;
}

t_chunk	*increase_heap(int zone, size_t size) {
	t_page *new_page = NULL;
	t_chunk *new_chunk = NULL;
	size_t alloc_size = 0;

	if (zone == 2)
		alloc_size = size;
	else
		alloc_size = zone_size(zone);
	// PAGE
	new_page = ft_alloc(PAGE_OVERHEAD + alloc_size);
	new_page->malloc_list = NULL;
	new_page->free_list = NULL;
	new_page->next = NULL;
	// CHUNK
	new_chunk = (t_chunk *)((size_t)new_page + PAGE_OVERHEAD);
	new_chunk->prev = NULL;
	new_chunk->size = alloc_size;
	new_chunk->next = NULL;
	// LISTS
	add_chunk_to_list(&new_page->free_list, new_chunk);
	alloc(&new_page, new_chunk, size);

	add_page_to_list(zone, new_page);
	return new_chunk;
}

void	*find_in_list(size_t size, t_chunk *free_list) {
	t_chunk *tmp = free_list;
	while (tmp) {
		if (tmp->size >= size)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void	*find_in_zone(size_t size, int zone) {
	void *found = NULL;
	t_page *tmp = g_page[zone];

	while (tmp) {
		if ((found = find_in_list(size, tmp->free_list)))
			return alloc(&tmp, found, size);
		tmp = tmp->next;
	}
	return NULL;
}

void	*find_free(size_t size, int begin_zone) {
	void *found = NULL;

	while (begin_zone < 3) {
		if ((found = find_in_zone(size, begin_zone)))
			return found;
		begin_zone++;
	}
	return NULL;
}

void	*page_head(t_chunk *chunk) {
	t_chunk *tmp = chunk;
	while (tmp->prev)
		tmp = tmp->prev;
	return (void *)tmp - PAGE_OVERHEAD;
}

void	merge_chunk(t_chunk **list, t_chunk *chunk) {
	if (chunk->prev) {
		// MERGE PREV
		if ((void*)chunk->prev + chunk->prev->size == chunk) {
			chunk->prev->size += chunk->size;
			remove_chunk_from_list(list, chunk);
			chunk = chunk->prev;
		}
	}
	if (chunk->next) {
		if ((void*)chunk + chunk->size == (void*)chunk->next) {
			chunk->size += chunk->next->size;
			remove_chunk_from_list(list, chunk->next);
		}
	}
}

void	free(void *ptr) {
	t_page *page = NULL;
	if (!ptr)
		return;
	ptr = ptr - CHUNK_OVERHEAD;
	page = (t_page *)page_head(ptr);
	remove_chunk_from_list(&page->malloc_list, ptr);
	add_chunk_to_list(&page->free_list, ptr);
	merge_chunk(&page->free_list, ptr);
	//show_alloc_mem();
	//show_free_mem();
}

void	*malloc(size_t size) {
	size += CHUNK_OVERHEAD;
	int zone = get_zone(size);
	void *ret = find_free(size, zone);
	if (!ret)
		ret = increase_heap(zone, size);
	//show_alloc_mem();
	//show_free_mem();
	return ret + CHUNK_OVERHEAD;
}
