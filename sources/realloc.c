/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:13:28 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/06 00:51:39 by lumenthi         ###   ########.fr       */
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
	if (!ptr || invalid_address(ptr))
		return malloc(size);
	void *header = CHUNK_HEADER(ptr);
	if (!is_valid(header))
		return malloc(size);
	void *new_ptr = malloc(size);
	ft_memmove(new_ptr, ptr, size);
	free(ptr);
	return new_ptr;
}
