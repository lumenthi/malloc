/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 01:30:41 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/11 00:51:01 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

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
