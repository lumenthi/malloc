/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 01:32:22 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/10 13:52:44 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

// DEBUG, REMOVE AFTER

int		debug = 1;

void	debug_address(void *address, char *str) {
	ft_putaddress(address);
	ft_putstr(": ");
	ft_putstr(str);
	ft_putchar('\n');
}

void	debug_character(char value, char *name) {
	ft_putchar(value);
	ft_putstr(": ");
	ft_putstr(name);
	ft_putchar('\n');
}

void	debug_size(size_t size, char *name) {
	ft_putstr(name);
	ft_putstr(": ");
	ft_putnbr(size);
	ft_putchar('\n');
}

//////////////////////////

void	*page_head(t_chunk *chunk) {
	t_chunk *tmp = chunk;
	while (tmp->prev)
		tmp = tmp->prev;
	return (void *)tmp - PAGE_OVERHEAD;
}

int		get_zone(size_t size) {
	if (size > TINY) {
		if (size > SMALL)
			return LARGE_P;
		return SMALL_P;
	}
	return TINY_P;
}

size_t	zone_size(int zone) {
	if (zone == TINY_P)
		return TINY;
	else
		return SMALL;
}

int		is_valid(void *tmp) {
	char *t = tmp;
	//debug_address((t-1), "t-1");
	//debug_address(t, "t");
	//debug_address(t + CHUNK_OVERHEAD, "t + CHUNK_OVERHEAD");
	if (t && *(t - 1) == '\0' && *(t + CHUNK_OVERHEAD) == '\0') {
		//ft_putstr("VALID\n");
		return 1;
	}
	//ft_putstr("INVALID\n");
	return 0;
}

void	*ft_alloc(size_t size) {
	void *ret;

	ret = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (ret == MAP_FAILED)
		ft_exit("MMAP ERROR, CANT MAP NECESSARY MEMORY, EXITING\n");
	return (ret);
}
