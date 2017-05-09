/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 22:23:43 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:52:17 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*listnew;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	listnew = f(lst);
	lst = lst->next;
	tmp = listnew;
	while (lst)
	{
		tmp->next = f(lst);
		if (!(tmp->next))
		{
			ft_lstdel(&listnew, ft_bzero);
			return (NULL);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
	return (listnew);
}
