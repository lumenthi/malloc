/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:00:19 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/01 02:47:13 by lumenthi         ###   ########.fr       */
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

void	*find_in_list(size_t size, t_chunk *free_list) {
	t_chunk *tmp = free_list;
	(void)size;
	while (tmp) {
		tmp = tmp->next;
	}
	return NULL;
}

void	*find_in_zone(size_t size, int zone) {
	void *found = NULL;
	t_page *tmp = g_page[zone];

	while (tmp) {
		if ((found = find_in_list(size, tmp->free_list)))
			return found;
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
		*list = chunk;
		return ;
	}
	if (chunk < *list) {
		chunk->next = *list;
		*list = chunk;
		return ;
	}
	while (tmp->next != NULL && tmp < tmp->next)
		tmp = tmp->next;
	if (tmp->next) {
		chunk->next = tmp->next;
		tmp->next->prev = chunk;
	}
	tmp->next = chunk;
	chunk->prev = tmp;
}

void	remove_chunk_from_list(t_chunk **list, t_chunk *chunk) {
	if (*list == chunk)
		*list = chunk->next;
	if (chunk->next)
		chunk->next->prev = chunk->prev;
	if (chunk->prev)
		chunk->prev->next = chunk->next;
}

t_chunk	*alloc(t_page **page, t_chunk *free_chunk, size_t size) {
	(void)size;
	(void)page;
	t_chunk **malloc_list = &(*page)->malloc_list;
	t_chunk **free_list = &(*page)->free_list;
	size_t remaining = 0;
	t_chunk *new_chunk = NULL;
	// REMOVE FROM FREE_LIST
	remove_chunk_from_list(free_list, free_chunk);
	// SPLIT
	ft_putnbr(free_chunk->size);
	ft_putstr(" - ");
	ft_putnbr(size);
	ft_putchar('\n');
	remaining = free_chunk->size - size;
	ft_putstr("REMAINING: ");
	ft_putnbr(remaining);
	ft_putchar('\n');
	(void)new_chunk;
   /* if (size < free_chunk->size) {*/
		/*if (remaining > CHUNK_OVERHEAD) {*/
			/*new_chunk->prev = NULL;*/
			/*new_chunk->size = remaining;*/
			/*// free_chunk + size = */
		/*}*/
	/*}*/
	// ADD TO MALLOC_LIST
	add_chunk_to_list(malloc_list, free_chunk);
	return NULL;
}

t_page	*new_page(int zone, size_t size) {
	t_page *new_page = NULL;
	t_chunk *new_chunk = NULL;
	size_t alloc_size = 0;

	if (zone == 2)
		alloc_size = size;
	else
		alloc_size = zone_size(zone);
	new_page = ft_alloc(PAGE_OVERHEAD + alloc_size);
	// CHUNK
	new_chunk = (t_chunk *)(new_page + PAGE_OVERHEAD);
	new_chunk->prev = NULL;
	new_chunk->size = alloc_size - CHUNK_OVERHEAD;
	new_chunk->next = NULL;
	// PAGE
	new_page->malloc_list = NULL;
	add_chunk_to_list(&new_page->free_list, new_chunk);
	alloc(&new_page, new_chunk, size);
	new_page->next = NULL;
	add_page_to_list(zone, new_page);
	return new_page;
}

void	*malloc(size_t size) {
	size += CHUNK_OVERHEAD;
	int zone = get_zone(size);
	void *ret = find_free(size, zone);
	// ret ? ft_putstr("FOUND\n") : ft_putstr("NULL\n");
	if (!ret) {
		new_page(zone, size);
	}
	show_free_mem();
	show_alloc_mem();
	return ret;
}
