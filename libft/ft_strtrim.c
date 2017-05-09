/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 17:23:51 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:57:52 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*src;
	char	*str;
	size_t	len;
	size_t	i;

	src = (char *)s;
	while (*src == ' ' || *src == '\n' || *src == '\t')
		src++;
	len = 0;
	while (src[len])
		len++;
	while ((src[len - 1] == ' ' || src[len - 1] == '\n' ||
		src[len - 1] == '\t') && len > 0)
		len--;
	str = ft_strnew(len);
	if (!str)
		return (str);
	i = 0;
	while (len--)
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}
