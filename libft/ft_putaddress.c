/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <lumenthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 13:49:00 by lumenthi          #+#    #+#             */
/*   Updated: 2018/09/18 13:51:28 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int   hex_len(size_t input)
{
  int i;

  i = 0;
  while ((input >>= 4) > 0)
    i++;
  return (i);
}

void        ft_putaddress(size_t input)
{
  char    HEX_ARRAY[17];
  int     i;
  int     len;

  i = 0;
  len = hex_len(input);
  ft_strcpy(HEX_ARRAY, "0123456789ABCDEF");
  ft_putstr("0x");
  while (i <= len)
  {
      ft_putchar(HEX_ARRAY[((input >> (4 * (len))) & 0xF)]);
      input <<= 4;
      i++;
  }
}
