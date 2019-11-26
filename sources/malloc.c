/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:00:19 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/26 20:13:02 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

t_manager	*g_manager = NULL;

void	*ft_alloc(size_t size) {
	void *ret;

	ret = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (ret == MAP_FAILED)
		ft_exit("MMAP ERROR, CANT MAP NECESSARY MEMORY, EXITING\n");
	return (ret);
}

t_mapped_element *new_memory_element(size_t size) {
	t_mapped_element *ret;

	ret = (t_mapped_element *)ft_alloc(sizeof(t_mapped_element));
	ret->addr = (void *)ft_alloc(size);
	ret->size = size;
	ret->next = NULL;
	return ret;
}

int		return_size(size_t size) {
	int i;

	i = 0;
	if (size >= TINY) {
		i = 1;
		if (size >= SMALL) {
			i = 2;
			if (size >= LARGE)
				i = 3;
		}
	}
	return i;
}

size_t get_size(int category, size_t size) {
	if (category == 0)
		return TINY;
	if (category == 1)
		return SMALL;
	if (category == 2)
		return LARGE;
	return size;
}

void	map_memory(size_t size) {
	size_t category = return_size(size);
	t_mapped_element **head = &g_manager->mapped_memory[category];
	t_mapped_element *last = *head;

	if (*head == NULL) {
		*head = new_memory_element(get_size(category, size));
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_memory_element(get_size(category, size));
}

void	initialization(void) {
	int i;

	i = 0;
	g_manager = (t_manager *)ft_alloc(sizeof(t_manager));
	while (i < 4) {
		g_manager->bin[i] = NULL;
		g_manager->mapped_memory[i] = NULL;
		i++;
	}
}

void	*malloc(size_t size) {
	if (g_manager == NULL)
		initialization();
	map_memory(size);
	show_alloc_mem();
	(void)size;
	return NULL;
}
