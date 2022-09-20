/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:59:01 by tgildero          #+#    #+#             */
/*   Updated: 2020/10/30 18:41:58 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;
	size_t	j;

	len_src = 0;
	len_dst = 0;
	while (src[len_src] != '\0')
		len_src++;
	while (dst[len_dst] != '\0')
		len_dst++;
	j = len_dst;
	i = 0;
	if (len_dst < size - 1 && size > 0)
	{
		while (src[i] != '\0' && len_dst + i < size - 1)
		{
			dst[j++] = src[i++];
		}
		dst[j] = '\0';
	}
	if (len_dst >= size)
		len_dst = size;
	return (len_dst + len_src);
}
