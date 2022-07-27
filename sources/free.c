/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:51:10 by lumenthi          #+#    #+#             */
/*   Updated: 2022/07/27 12:05:14 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	free(void *ptr) {
	pthread_mutex_lock(&g_malloc_mutex);
	t_page *page = NULL;
	if (!ptr) {
		pthread_mutex_unlock(&g_malloc_mutex);
		return;
	}
	t_chunk *header = CHUNK_HEADER(ptr);
	if (!(page = valid_address(header))) {
		pthread_mutex_unlock(&g_malloc_mutex);
		return;
	}
	remove_chunk_from_list(&page->malloc_list, header);
	add_chunk_to_list(&page->free_list, header);
	merge_chunk(&page->free_list, header);
	if (page->malloc_list == NULL) {
		int zone = get_zone_p(page->size);
		if (zone < 2) {
			if (g_page[zone]->next == NULL) {
				pthread_mutex_unlock(&g_malloc_mutex);
				return ;
			}
		}
		remove_page_from_list(&g_page[zone], page);
		ft_free(page);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
}
