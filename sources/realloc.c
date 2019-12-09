/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:13:28 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/09 01:32:39 by lumenthi         ###   ########.fr       */
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
	void *header = CHUNK_HEADER(ptr);
	if (invalid_address(header) || !is_valid(header)) {
		if (debug)
			ft_putstr("\nreturn not valid;\n");
		return malloc(size);
	}
	free(ptr);
	void *new_ptr = malloc(size);
	ft_memmove(new_ptr, ptr, size);
	if (debug) {
		ft_putstr("return ");
		ft_putaddress(new_ptr);
		ft_putstr(";\n");
	}
	return new_ptr;
}
