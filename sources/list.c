/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 01:30:41 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/12 01:11:00 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	add_page_to_list(t_page **list, t_page *page) {
	t_page *cur = NULL;
	if (*list == NULL || *list >= page) {
		page->next = *list;
		*list = page;
	}
	else {
		cur = *list;
		while (cur->next != NULL && cur->next < page)
			cur = cur->next;
		page->next = cur->next;
		cur->next = page;
	}
}

void	remove_page_from_list(t_page **list, t_page *page) {
	t_page *prev = NULL;
	t_page *cur = NULL;
	cur = *list;
	while (cur) {
		if (cur == page) {
			if (prev == NULL)
				*list = cur->next;
			else {
				prev->next = cur->next;
			}
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
	return ;
}

void	add_chunk_to_list(t_chunk **list, t_chunk *chunk) {
	if (*list == NULL) {
		*list = chunk;
	}
	else if (*list >= chunk) {
		chunk->next = *list;
		chunk->next->prev = chunk;
		*list = chunk;
	}
	else {
		t_chunk *tmp = *list;
		while (tmp->next != NULL && tmp->next < chunk)
			tmp = tmp->next;
		chunk->next = tmp->next;
		if (tmp->next != NULL)
			chunk->next->prev = chunk;
		tmp->next = chunk;
		chunk->prev = tmp;
	}
}

void	remove_chunk_from_list(t_chunk **list, t_chunk *chunk) {
	if (*list == NULL || chunk == NULL)
		return;
	if (*list == chunk)
		*list = chunk->next;
	if (chunk->next != NULL)
		chunk->next->prev = chunk->prev;
	if (chunk->prev != NULL)
		chunk->prev->next = chunk->next;
	chunk->prev = NULL;
	chunk->next = NULL;
	return ;
}

void	merge_chunk(t_chunk **list, t_chunk *chunk) {
	if (chunk->next) {
		if ((void*)chunk + chunk->size == (void*)chunk->next) {
			chunk->size += chunk->next->size;
			remove_chunk_from_list(list, chunk->next);
		}
	}
	if (chunk->prev) {
		if ((void*)chunk->prev + chunk->prev->size == chunk) {
			chunk->prev->size += chunk->size;
			chunk = chunk->prev;
			remove_chunk_from_list(list, chunk->next);
		}
	}
}
