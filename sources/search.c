/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 01:27:30 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/12 01:16:57 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

static void	*find_in_list(size_t size, t_chunk *free_list) {
	t_chunk *tmp = free_list;
	while (tmp) {
		if (tmp->size >= size)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

static void	*find_in_zone(size_t size, int zone) {
	void *found = NULL;
	t_page *tmp = g_page[zone];

	while (tmp) {
		if ((found = find_in_list(size, tmp->free_list))) {
			return alloc(&tmp, found, size);
		}
		tmp = tmp->next;
	}
	return NULL;
}

void	*find_free(size_t size, int begin_zone) {
	void *found = NULL;

	while (begin_zone < 3) {
		if ((found = find_in_zone(size, begin_zone))) {
			return found;
		}
		begin_zone++;
	}
	return NULL;
}

t_page		*valid_address(void *ptr) {
	t_chunk *tmp;
	t_page *page = NULL;
	int i = 0;

	while (i < 3) {
		page = g_page[i];
		while (page) {
			tmp = page->malloc_list;
			while (tmp) {
				if (tmp == ptr)
					return page;
				tmp = tmp->next;
			}
			page = page->next;
		}
		i++;
	}
	return NULL;
}
