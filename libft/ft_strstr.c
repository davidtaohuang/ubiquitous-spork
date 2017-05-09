/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 20:00:35 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:57:43 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int	ft_insearch(const char *big, const char *little)
{
	if (!(*little))
		return (1);
	if (*big != *little)
		return (0);
	return (ft_insearch(++big, ++little));
}

char		*ft_strstr(const char *big, const char *little)
{
	if (!(*little))
		return ((char*)big);
	while (*big)
	{
		if (*big == *little)
		{
			if (ft_insearch(big, little))
				return ((char*)big);
		}
		big++;
	}
	return (NULL);
}
