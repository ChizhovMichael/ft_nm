/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:11:47 by tgildero          #+#    #+#             */
/*   Updated: 2020/11/03 12:14:06 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *el;

	if (*lst)
	{
		el = ft_lstlast(*lst);
		el->next = &*new;
	}
	else
	{
		*lst = new;
	}
}
