/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:43:49 by tgildero          #+#    #+#             */
/*   Updated: 2020/11/07 13:07:09 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;

	dst_tmp = (unsigned char *)dst;
	src_tmp = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	if (dst > src)
	{
		while (len > 0)
		{
			dst_tmp[len - 1] = src_tmp[len - 1];
			len--;
		}
	}
	else
	{
		while (len--)
		{
			*dst_tmp++ = *src_tmp++;
		}
	}
	return (dst);
}
