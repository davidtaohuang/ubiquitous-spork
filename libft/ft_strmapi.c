/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 23:08:55 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:56:33 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*str;

	len = 0;
	while (s[len])
		len++;
	str = ft_strnew(len);
	if (!str)
		return (str);
	while (len-- > 0)
		str[len] = f(len, s[len]);
	return (str);
}
