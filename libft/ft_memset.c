/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:53:09 by tgildero          #+#    #+#             */
/*   Updated: 2020/10/28 20:46:53 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *tmp_mem;

	tmp_mem = (unsigned char *)b;
	while (len > 0)
	{
		*tmp_mem++ = (unsigned char)c;
		len--;
	}
	return (b);
}
