/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinreplace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 16:45:28 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/16 16:45:28 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoinreplace(char const *s1, char const *s2)
{
	char	*s;
	size_t	n;

	n = (size_t)(ft_strlen(s1) + ft_strlen(s2));
	s = ft_strnew(n);
	if (!s)
		return (s);
	ft_strcpy(s, s1);
	ft_strcat(s, s2);
	ft_memdel((void**)&s1);
	return (s);
}
