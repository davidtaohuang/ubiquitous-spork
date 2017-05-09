/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 18:55:22 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:52:20 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlist;

	newlist = (t_list*)malloc(sizeof(t_list));
	if (newlist)
	{
		if (!content)
		{
			newlist->content_size = 0;
			newlist->content = NULL;
		}
		else
		{
			newlist->content = ft_memalloc(content_size);
			newlist->content_size = content_size;
			ft_memmove(newlist->content, content, content_size);
		}
		newlist->next = NULL;
	}
	return (newlist);
}
