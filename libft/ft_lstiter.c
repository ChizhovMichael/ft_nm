/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 22:06:47 by tgildero          #+#    #+#             */
/*   Updated: 2020/11/04 22:25:07 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *list_ptr;

	list_ptr = lst;
	while (list_ptr)
	{
		(*f)(list_ptr->content);
		list_ptr = list_ptr->next;
	}
}
