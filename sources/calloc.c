/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:09:42 by lumenthi          #+#    #+#             */
/*   Updated: 2019/12/13 19:40:06 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manager.h"

void	*calloc(size_t nelem, size_t size) {
	void *ret = NULL;

	ret = malloc(nelem * size);
	if (ret) {
		ft_bzero(ret, nelem * size);
	}
	return (ret);
}
