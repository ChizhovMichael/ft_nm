/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:11:19 by tgildero          #+#    #+#             */
/*   Updated: 2020/10/28 18:43:15 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;
	size_t			i;

	i = 0;
	tmp_src = (unsigned char *)src;
	tmp_dst = (unsigned char *)dst;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		if (tmp_src[i] == (unsigned char)c)
		{
			return (dst + i + 1);
		}
		i++;
	}
	return (NULL);
}
