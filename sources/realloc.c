/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:13:28 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/12 12:35:11 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	*realloc(void *ptr, size_t size) {
	if (debug) {
		ft_putstr("realloc(");
		ft_putaddress(ptr);
		ft_putstr(", ");
		ft_putnbr(size);
		ft_putstr(");\n");
	}
	t_chunk *header = CHUNK_HEADER(ptr);
	//debug_address(header, "header");
	if (!valid_address(header)) {
		if (debug)
			ft_putstr("return not valid;\n");
		return malloc(size);
	}
	void *new_ptr = malloc(size);
	size = size > header->size ? header->size : size;
	ft_memmove(new_ptr, ptr, size);
	free(ptr);
	if (debug) {
		ft_putstr("return ");
		ft_putaddress(new_ptr);
		ft_putstr(";\n");
	}
	return new_ptr;
}
