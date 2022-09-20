/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:12:55 by tgildero          #+#    #+#             */
/*   Updated: 2020/11/07 13:44:26 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_issep(char c, char sep)
{
	return (c == sep);
}

static int		ft_wordcount(char *str, char sep)
{
	int		words;

	words = 0;
	while (*str)
	{
		if (!(words) && !(ft_issep(*str, sep)))
		{
			words++;
		}
		else if (ft_issep(*(str - 1), sep) && !(ft_issep(*str, sep)))
		{
			words++;
		}
		str++;
	}
	return (words);
}

static int		ft_len_word(char *str, int i, char sep)
{
	int		count;

	count = 0;
	while (!(ft_issep(str[i], sep)) && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

static	char	**ft_create_strs(char **arr, char *str, char sep)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_issep(str[i], sep) && str[i])
			i++;
		if (str[i])
		{
			k = 0;
			if (!(arr[j] = malloc(sizeof(char) * ft_len_word(str, i, sep) + 1)))
			{
				free(arr);
				return (NULL);
			}
			while (!ft_issep(str[i], sep) && str[i])
				arr[j][k++] = str[i++];
			arr[j++][k] = '\0';
		}
	}
	arr[j] = NULL;
	return (arr);
}

char			**ft_split(char *str, char sep)
{
	char	**arr;

	if (!str)
	{
		if (!(arr = malloc(sizeof(char *) * 1)))
			return (NULL);
		arr = NULL;
		return (arr);
	}
	if (!(arr = malloc(sizeof(char *) * (ft_wordcount(str, sep) + 1))))
		return (NULL);
	ft_create_strs(arr, str, sep);
	return (arr);
}
