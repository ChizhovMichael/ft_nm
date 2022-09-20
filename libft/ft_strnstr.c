/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:55:49 by tgildero          #+#    #+#             */
/*   Updated: 2020/11/07 13:12:07 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *find, size_t slen)
{
	size_t i;
	size_t j;

	if (!*find)
		return ((char *)s);
	i = 0;
	while (*(s + i) && i < slen)
	{
		if (*(s + i) == find[0])
		{
			j = 1;
			while (*(find + j) && *(s + i + j) == *(find + j) && (i + j) < slen)
			{
				j++;
			}
			if (*(find + j) == '\0')
			{
				return ((char *)s + i);
			}
		}
		i++;
	}
	return (NULL);
}
