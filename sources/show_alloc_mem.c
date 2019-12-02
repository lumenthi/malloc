/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:01:57 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/02 00:46:43 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	display_zone_name(int zone) {
	if (zone == TINY_P)
		ft_putstr("TINY : ");
	else if (zone == SMALL_P)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
}

void display_chunks(t_page *page, char mode) {
	t_chunk **head = mode == 'f' ? &page->free_list : &page->malloc_list;
	t_chunk *tmp = *head;

	if (mode == 'm')
		ft_putstr("ALLOCATED CHUNKS : \n");
	else
		ft_putstr("FREE CHUNKS :\n");
	while (tmp) {
		ft_putaddress((size_t)tmp + CHUNK_OVERHEAD);
		ft_putstr(" - ");
		ft_putaddress((size_t)tmp + tmp->size);
		ft_putstr(": ");
		ft_putnbr(tmp->size - CHUNK_OVERHEAD);
		ft_putstr(" octet(s)\n");
		tmp = tmp->next;
	}
}

void display_page(t_page *page, int zone, char mode) {
	t_page *tmp = page;

	while (tmp) {
		display_zone_name(zone);
		ft_putaddress((size_t)tmp);
		ft_putchar('\n');
		display_chunks(tmp, mode);
		tmp = tmp->next;
	}
}

void	show_free_mem() {
	int i = 0;

	while (i < 3) {
		display_page(g_page[i], i, 'f');
		i++;
	}
	ft_putstr("_____________________\n");
}

void	show_alloc_mem() {
	int i = 0;

	while (i < 3) {
		display_page(g_page[i], i, 'm');
		i++;
	}
	ft_putstr("_____________________\n");
}
