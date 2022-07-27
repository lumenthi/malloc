/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:13:28 by lumenthi          #+#    #+#             */
/*   Updated: 2022/07/27 11:52:17 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	*realloc(void *ptr, size_t size) {
	pthread_mutex_lock(&g_malloc_mutex);
	t_chunk *header = CHUNK_HEADER(ptr);
	if (!valid_address(header)) {
		pthread_mutex_unlock(&g_malloc_mutex);
		return malloc(size);
	}
	if (size + CHUNK_OVERHEAD <= header->size) {
		pthread_mutex_unlock(&g_malloc_mutex);
		return ptr;
	}
	pthread_mutex_unlock(&g_malloc_mutex);
	void *new_ptr = malloc(size);
	pthread_mutex_lock(&g_malloc_mutex);
	size = size > header->size ? header->size : size;
	ft_memmove(new_ptr, ptr, size);
	pthread_mutex_unlock(&g_malloc_mutex);
	free(ptr);
	return new_ptr;
}
