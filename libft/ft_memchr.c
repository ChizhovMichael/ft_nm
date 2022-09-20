/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:27:26 by tgildero          #+#    #+#             */
/*   Updated: 2020/10/28 21:10:31 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp_s;
	size_t			i;

	tmp_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (tmp_s[i] == (unsigned char)c)
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (NULL);
}
