/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:01:57 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/29 18:32:40 by lumenthi         ###   ########.fr       */
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

void display_page(t_page *page, int zone) {
	t_page *tmp = page;

	while (tmp) {
		display_zone_name(zone);
		tmp = tmp->next;
	}
}

void	show_alloc_mem() {
	int i = 0;

	while (i < 3) {
		display_page(g_page[i], i);
		i++;
	}
	ft_putstr("_____________________\n");
}
