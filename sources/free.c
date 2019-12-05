/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:51:10 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/05 01:35:03 by lumenthi         ###   ########.fr       */
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
	t_page *page = NULL;
	if (!ptr || invalid_address(ptr))
		return;
	ptr = CHUNK_HEADER(ptr);
	if (!is_valid(ptr))
		return;
	page = (t_page *)page_head(ptr);
	remove_chunk_from_list(&page->malloc_list, ptr);
	add_chunk_to_list(&page->free_list, ptr);
	merge_chunk(&page->free_list, ptr);
}
