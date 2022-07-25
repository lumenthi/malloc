/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:13:28 by lumenthi          #+#    #+#             */
/*   Updated: 2022/07/25 11:26:53 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	*realloc(void *ptr, size_t size) {
	t_chunk *header = CHUNK_HEADER(ptr);
	if (!valid_address(header))
		return malloc(size);
	if (size + CHUNK_OVERHEAD <= header->size)
		return ptr;
	void *new_ptr = malloc(size);
	size = size > header->size ? header->size : size;
	ft_memmove(new_ptr, ptr, size);
	free(ptr);
	return new_ptr;
}
