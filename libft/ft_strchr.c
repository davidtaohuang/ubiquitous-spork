/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 21:41:44 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:54:25 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	a;
	char	*str;

	a = (char)c;
	str = (char*)s;
	while (*str)
	{
		if (*str == a)
			return (str);
		str++;
	}
	if (*str == a)
		return (str);
	return (NULL);
}
