/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:09:42 by lumenthi          #+#    #+#             */
/*   Updated: 2022/07/27 12:37:29 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	*calloc(size_t nelem, size_t size) {
	pthread_mutex_lock(&g_malloc_mutex);
	void *ret = NULL;

	ret = malloc(nelem * size);
	if (ret) {
		ft_bzero(ret, nelem * size);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
	return (ret);
}
