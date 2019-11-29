/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:00:19 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/29 01:53:29 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

t_page	*g_pages[3] = {NULL, NULL, NULL};

void	*ft_alloc(size_t size) {
	void *ret;

	ret = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (ret == MAP_FAILED)
		ft_exit("MMAP ERROR, CANT MAP NECESSARY MEMORY, EXITING\n");
	return (ret);
}

int		get_zone(size_t size) {
	if (size > TINY) {
		if (size > SMALL)
			return LARGE_P;
		return SMALL_P;
	}
	return TINY_P;
}

void	*find_in_list(size_t size, t_chunk *free_list) {
	t_chunk *tmp = free_list;
	(void)size;
	while (tmp) {
		tmp = tmp->next;
	}
	return NULL;
}

void	*find_in_zone(size_t size, int zone) {
	void *found = NULL;
	t_page *tmp = g_pages[zone];

	while (tmp) {
		if ((found = find_in_list(size, tmp->free_list)))
			return found;
		tmp = tmp->next;
	}
	return NULL;
}

void	*find_free(size_t size, int begin_zone) {
	void *found = NULL;

	while (begin_zone < 3) {
		if ((found = find_in_zone(size, begin_zone)))
			return found;
		begin_zone++;
	}
	return NULL;
}

void	*malloc(size_t size) {
	void *ret = find_free(size, get_zone(size));
	ret ? ft_putstr("FOUND") : ft_putstr("NULL");
	return ret;
}
