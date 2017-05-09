/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 23:03:40 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:56:28 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		len;
	char	*str;

	len = 0;
	while (s[len])
		len++;
	str = ft_strnew(len);
	if (!str)
		return (str);
	while (len-- > 0)
		str[len] = f(s[len]);
	return (str);
}
