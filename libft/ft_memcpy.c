/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:14:20 by tgildero          #+#    #+#             */
/*   Updated: 2020/10/28 19:00:38 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *tmp_src;
	unsigned char *tmp_dst;

	if (n == 0 || src == dst)
		return (dst);
	tmp_src = (unsigned char *)src;
	tmp_dst = (unsigned char *)dst;
	while (n > 0)
	{
		*tmp_dst++ = *tmp_src++;
		n--;
	}
	return (dst);
}
