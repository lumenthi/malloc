/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:01:14 by lumenthi          #+#    #+#             */
/*   Updated: 2019/11/28 01:00:52 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_H
# define MANAGER_H

# include <sys/mman.h>
# include "libft.h"

// DEFINE
# define OVERHEAD		sizeof(t_free_block)
# define HEADER(addr)	*(addr - OVERHEAD)
// 64bits
//# define TINY 992
//# define SMALL 15360
//# define LARGE ?????

//32 bits
# define TINY 10//496
# define SMALL 20//15359
# define LARGE 40//?????

// STRUCTURES
typedef struct				s_free_block {
	struct s_free_block		*prev;
	size_t					prev_size;
	size_t					size;
	struct s_free_block		*next;
	size_t					next_size;
}							t_free_block;

extern t_free_block			*g_bin[4]; // [0- TINY, 1- SMALL, 2- LARGE, 3- >LARGE]
void						show_alloc_mem();

#endif
