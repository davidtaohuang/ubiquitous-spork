/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 21:59:38 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:57:23 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*loc;
	char	a;

	a = (char)c;
	str = (char*)s;
	loc = NULL;
	while (*str)
	{
		if (*str == a)
			loc = str;
		str++;
	}
	if (*str == a)
		loc = str;
	return (loc);
}
