/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmemdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 21:40:41 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/05 21:48:21 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

void	ft_lstmemdel(t_list **alst)
{
	t_list *tmp;

	while (*alst)
	{
		free((*alst)->content);
		(*alst)->content = NULL;
		tmp = (*alst)->next;
		free(*alst);
		*alst = NULL;
		*alst = tmp;
	}
}
