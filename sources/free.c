/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:51:10 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/10 01:15:20 by lumenthi         ###   ########.fr       */
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
		ft_putstr(");");
	}
	t_page *page = NULL;
	if (!ptr) {
		if (debug)
			ft_putstr("\nreturn no ptr;\n");
		return;
	}
	ptr = CHUNK_HEADER(ptr);
	if (invalid_address(ptr) || !is_valid(ptr)) {
		if (debug)
			ft_putstr("\nreturn not valid;\n");
		return;
	}
	page = (t_page *)page_head(ptr);
	remove_chunk_from_list(&page->malloc_list, ptr);
	add_chunk_to_list(&page->free_list, ptr);
	merge_chunk(&page->free_list, ptr);
	// show_alloc_mem();
	// show_free_mem();
	if (debug)
		ft_putstr("\nreturn;\n");
}
