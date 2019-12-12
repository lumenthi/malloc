/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:51:10 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/12 01:50:33 by lumenthi         ###   ########.fr       */
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
	if (!(page = valid_address(header))) {
		if (debug)
			ft_putstr("\nreturn not valid ptr;\n");
		return;
	}
	remove_chunk_from_list(&page->malloc_list, header);
	add_chunk_to_list(&page->free_list, header);
	merge_chunk(&page->free_list, header);
	if (page->malloc_list == NULL) {
		int zone = get_zone(page->size);
		if (zone < 2) {
			if (g_page[zone]->next == NULL) {
				if (debug)
					ft_putstr("\nreturn;\n");
				return ;
			}
		}
		remove_page_from_list(&g_page[zone], page);
		ft_free(page);
	}
	//show_alloc_mem();
	//show_free_mem();
	if (debug)
		ft_putstr("\nreturn;\n");
}
