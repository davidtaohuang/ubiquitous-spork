/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 15:13:53 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:55:29 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

static size_t	ft_strlenlocal(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

char			*ft_strdup(const char *s1)
{
	char	*s;
	size_t	i;

	s = ft_strnew(ft_strlenlocal(s1));
	if (!s)
		return (NULL);
	if (s1)
	{
		i = 0;
		while (s1[i])
		{
			s[i] = s1[i];
			i++;
		}
	}
	return (s);
}
