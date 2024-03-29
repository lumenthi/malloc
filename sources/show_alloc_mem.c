/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:01:57 by lumenthi          #+#    #+#             */
/*   Updated: 2022/07/27 12:36:40 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

static void	display_zone_name(int zone) {
	if (zone == TINY_P)
		ft_putstr("TINY : ");
	else if (zone == SMALL_P)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
}

static size_t	display_chunks(t_page *page, char mode) {
	t_chunk *head = mode == 'f' ? page->free_list : page->malloc_list;
	t_chunk *tmp = head;
	size_t	total = 0;

	while (tmp) {
		ft_putaddress((void *)tmp + CHUNK_OVERHEAD);
		ft_putstr(" - ");
		ft_putaddress((void *)tmp + tmp->size);
		ft_putstr(": ");
		ft_putnbr(tmp->size - CHUNK_OVERHEAD);
		ft_putstr(" octets\n");
		total += tmp->size - CHUNK_OVERHEAD;
		tmp = tmp->next;
	}
	return total;
}

static size_t	display_page(t_page *page, int zone, char mode) {
	t_page *tmp = page;
	size_t total = 0;

	while (tmp) {
		if ((mode == 'f' && tmp->free_list) ||
			(mode == 'm' && tmp->malloc_list)) {
			display_zone_name(zone);
			ft_putaddress(tmp);
			ft_putchar('\n');
			total += display_chunks(tmp, mode);
		}
		tmp = tmp->next;
	}
	return total;
}

void	show_free_mem() {
	pthread_mutex_lock(&g_malloc_mutex);
	int i = 0;
	size_t total = 0;

	ft_putstr("FREE CHUNKS :\n");
	while (i < 3) {
		total += display_page(g_page[i], i, 'f');
		i++;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
	pthread_mutex_unlock(&g_malloc_mutex);
}

void	show_alloc_mem() {
	pthread_mutex_lock(&g_malloc_mutex);
	int i = 0;
	size_t total = 0;

	ft_putstr("ALLOCATED CHUNKS : \n");
	while (i < 3) {
		total += display_page(g_page[i], i, 'm');
		i++;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
	pthread_mutex_unlock(&g_malloc_mutex);
}
