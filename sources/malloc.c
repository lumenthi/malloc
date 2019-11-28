/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:00:19 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/28 01:05:38 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

t_free_block	*g_bin[4] = {NULL, NULL, NULL, NULL};

void	*ft_alloc(size_t size) {
	void *ret;

	ret = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (ret == MAP_FAILED)
		ft_exit("MMAP ERROR, CANT MAP NECESSARY MEMORY, EXITING\n");
	return (ret);
}

void	*malloc(size_t size) {
	(void)size;
	if (g_bin[0] == NULL) {
		ft_putstr("NULL");
	}
	else
		ft_putstr("ALLOC");
	g_bin[0] = ft_alloc(10);
	return NULL;
}
