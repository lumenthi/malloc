/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:51:10 by lumenthi          #+#    #+#             */
/*   Updated: 2022/07/25 11:27:32 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	free(void *ptr) {
	t_page *page = NULL;
	if (!ptr)
		return;
	t_chunk *header = CHUNK_HEADER(ptr);
	if (!(page = valid_address(header)))
		return;
	remove_chunk_from_list(&page->malloc_list, header);
	add_chunk_to_list(&page->free_list, header);
	merge_chunk(&page->free_list, header);
	if (page->malloc_list == NULL) {
		int zone = get_zone(page->size);
		if (zone < 2)
			if (g_page[zone]->next == NULL)
				return ;
		remove_page_from_list(&g_page[zone], page);
		ft_free(page);
	}
}
