/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maxmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 23:16:44 by dhuang            #+#    #+#             */
/*   Updated: 2016/11/01 16:02:54 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "includes/libft.h"

int		*ft_maxmap(int *n, size_t l)
{
	int		*max;
	size_t	i;

	if (!n)
		return (NULL);
	max = n;
	i = 1;
	while (i++ < l)
	{
		n++;
		if (*n > *max)
			max = n;
	}
	return (max);
}
