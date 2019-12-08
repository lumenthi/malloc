/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 01:30:41 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/08 03:03:04 by lumenthi         ###   ########.fr       */
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
	debug_address(chunk, "chunk");
	debug_address(chunk->next, "chunk->next");
	t_chunk	*tmp = *list;
	if (*list == NULL) {
		ft_putstr("1");
		chunk->prev = NULL;
		*list = chunk;
		return ;
	}
	if (chunk < *list) {
		ft_putstr("2");
		chunk->prev = NULL;
		chunk->next = *list;
		(*list)->prev = chunk;
		*list = chunk;
		return ;
	}
	while (is_valid(tmp->next) && chunk > tmp->next) {
		tmp = tmp->next;
	}
	if (is_valid(tmp->next)) {
		debug_address(tmp, "tmp");
		debug_address(tmp->next, "tmp->next");
		ft_putstr("3");
		chunk->next = tmp->next;
		tmp->next->prev = chunk;
	}
	else {
		ft_putstr("4");
		chunk->next = NULL;
	}
	tmp->next = chunk;
	chunk->prev = tmp;
	debug_address(tmp, "tmp");
	while (tmp->next) {
		tmp = tmp->next;
	}
	ft_putstr("\nEND\n");
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
