/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:18:13 by tgildero          #+#    #+#             */
/*   Updated: 2020/11/02 18:34:01 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*start;

	if (!s1 && !s2)
		return (0);
	if (!(result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	if ((start = result))
	{
		if (s1)
		{
			while (*s1)
				*result++ = *s1++;
		}
		if (s2)
		{
			while (*s2)
				*result++ = *s2++;
		}
		*result = '\0';
	}
	return (start);
}
