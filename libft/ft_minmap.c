/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 23:19:10 by dhuang            #+#    #+#             */
/*   Updated: 2016/11/01 16:03:32 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "includes/libft.h"

int		*ft_minmap(int *n, size_t l)
{
	int		*min;
	size_t	i;

	if (!n)
		return (NULL);
	min = n;
	i = 1;
	while (i++ < l)
	{
		n++;
		if (*n < *min)
			min = n;
	}
	return (min);
}
