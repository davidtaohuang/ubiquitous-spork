/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 21:36:49 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/09 21:52:24 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
