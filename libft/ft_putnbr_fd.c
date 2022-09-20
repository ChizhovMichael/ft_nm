/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 10:58:14 by tgildero          #+#    #+#             */
/*   Updated: 2020/11/03 11:13:37 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	i;
	int	n_tmp;
	int	diff;

	n_tmp = n;
	i = 1;
	if (n < 0)
		write(fd, "-", 1);
	while (n_tmp / 10 != 0)
	{
		n_tmp = n_tmp / 10;
		i = i * 10;
	}
	while (i > 0)
	{
		diff = n / i;
		n = n % i;
		if (diff < 0)
		{
			diff = ~diff + 1;
		}
		diff = diff + '0';
		write(fd, &diff, 1);
		i = i / 10;
	}
}
