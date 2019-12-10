/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:51:10 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/10 14:09:27 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

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
	t_chunk *header = CHUNK_HEADER(ptr);
	if (invalid_address(header)) {
		if (debug)
			ft_putstr("\nreturn not valid ptr;\n");
		return;
	}
	page = (t_page *)page_head(header);
	debug_address(header, "header");
	debug_address(page, "page");
	remove_chunk_from_list(&page->malloc_list, header);
	add_chunk_to_list(&page->free_list, header);
	show_free_mem();
	merge_chunk(&page->free_list, header);
	//show_alloc_mem();
	//show_free_mem();
	if (debug)
		ft_putstr("\nreturn;\n");
}
