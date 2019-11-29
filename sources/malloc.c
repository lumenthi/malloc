/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:00:19 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/29 19:14:43 by lumenthi         ###   ########.fr       */
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
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_page;
}

t_page	*new_page(int zone, size_t size) {
	t_page *new_page = NULL;
	size_t alloc_size = 0;

	if (zone == 2)
		alloc_size = size;
	else
		alloc_size = zone_size(zone);
	new_page = ft_alloc(PAGE_OVERHEAD + alloc_size);
	new_page->malloc_list = NULL;
	new_page->free_list = NULL;
	new_page->next = NULL;
	add_page_to_list(zone, new_page);
	return new_page;
}

void	*malloc(size_t size) {
	int zone = get_zone(size);
	void *ret = find_free(size, zone);
	// ret ? ft_putstr("FOUND\n") : ft_putstr("\nNULL");
	if (!ret) {
		new_page(zone, size);
	}
	show_alloc_mem();
	return ret;
}
