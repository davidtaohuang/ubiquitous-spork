/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 22:28:08 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:55:40 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	n;

	n = (int)(ft_strlen(s1) + ft_strlen(s2));
	s = ft_strnew(n);
	if (!s)
		return (s);
	ft_strcpy(s, s1);
	ft_strcat(s, s2);
	return (s);
}
