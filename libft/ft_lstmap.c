/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgildero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:25:36 by tgildero          #+#    #+#             */
/*   Updated: 2020/11/07 14:45:25 by tgildero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *save;

	if (!lst || !f)
		return (NULL);
	if (!(new = ft_lstnew((*f)(lst->content))))
		return (0);
	save = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstnew((*f)(lst->content));
		if (!new->next)
		{
			ft_lstclear(&save, (*del));
			return (0);
		}
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (save);
}
