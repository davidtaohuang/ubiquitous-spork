/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 14:12:31 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 11:00:31 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t	ft_strlenlocal(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*s1;
	size_t	n;
	size_t	i;
	size_t	len;

	len = ft_strlenlocal(dest);
	if (len > size)
		return (ft_strlenlocal(src) + size);
	s1 = dest;
	i = 0;
	while (s1[i] && i < size)
		i++;
	n = 0;
	while (src[n] && i < size - 1)
		s1[i++] = src[n++];
	if (i < size)
		s1[i] = '\0';
	return (len + ft_strlenlocal(src));
}
