/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 01:32:22 by lumenthi          #+#    #+#             */
/*   Updated: 2022/07/27 11:18:03 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

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

int		get_zone_p(size_t size) {
	if (size > TINY_S) {
		if (size > SMALL_S)
			return LARGE_P;
		return SMALL_P;
	}
	return TINY_P;
}

size_t	zone_size(int zone) {
	if (zone == TINY_P)
		return TINY_S;
	else
		return SMALL_S;
}

void	*ft_alloc(size_t size) {
	void *ret;

	ret = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (ret == MAP_FAILED) {
		ft_putstr_fd("MMAP ERROR, CAN'T MAP NECESSARY MEMORY\n", STDERR_FILENO);
		return NULL;
	}
	return (ret);
}

void	ft_free(t_page *page) {
	if (munmap((void*)page, page->size) == -1)
		ft_putstr_fd("MUNMAP ERROR, CANT UNMAP MEMORY\n", STDERR_FILENO);
}
