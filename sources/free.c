/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:51:10 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/06 01:42:07 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

static void	merge_chunk(t_chunk **list, t_chunk *chunk) {
	if (chunk->prev) {
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
	if (debug) {
		ft_putstr("free(");
		ft_putaddress(ptr);
		ft_putstr(");\n");
	}
	t_page *page = NULL;
	if (!ptr || invalid_address(ptr))
		return;
	ptr = CHUNK_HEADER(ptr);
	if (!is_valid(ptr))
		return;
	ft_putstr("VALID\n");
	page = (t_page *)page_head(ptr);
	t_chunk *malloc_list = (t_chunk *)&page->malloc_list;
	t_chunk *free_list = (t_chunk *)&page->free_list;
	remove_chunk_from_list(&malloc_list, ptr);
	add_chunk_to_list(&free_list, ptr);
	merge_chunk(&free_list, ptr);
	show_alloc_mem();
	show_free_mem();
}
