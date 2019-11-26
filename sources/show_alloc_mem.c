/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:01:57 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/26 21:07:00 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

static void	print_category(int i, size_t size) {
	if (i == 0)
		ft_putstr("TINY: ");
	else if (i == 1)
		ft_putstr("SMALL: ");
	else if (i == 2)
		ft_putstr("LARGE: ");
	else {
		ft_putnbr(size);
		ft_putstr(": ");
	}
}

void	show_alloc_mem() {
	int i;
	t_mapped_element *tmp = NULL;

	i = 0;
	while (i < 4) {
		tmp = g_manager->mapped_memory[i];
		while (tmp) {
			print_category(i, tmp->size);
			ft_putaddress((size_t)tmp->addr);
			ft_putstr("\nSize: ");
			ft_putnbr(tmp->size);
			ft_putchar('\n');
			tmp = tmp->next;
		}
		i++;
	}
	ft_putstr("_____________________\n");
}
