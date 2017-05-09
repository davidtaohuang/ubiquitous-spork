/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 20:50:23 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:57:18 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	int	ft_insearch(const char *big, const char *little,
	size_t len, size_t i)
{
	while (*little)
	{
		if (*big++ != *little++ || i++ >= len)
			return (0);
	}
	return (1);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!(*little))
		return ((char*)big);
	i = 0;
	while (*big && i < len)
	{
		if (*big == *little)
		{
			if (ft_insearch(big, little, len, i))
				return ((char*)big);
		}
		big++;
		i++;
	}
	return (NULL);
}
