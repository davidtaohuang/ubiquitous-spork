/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 13:25:02 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:52:54 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*m;
	unsigned char	a;

	m = (unsigned char*)s;
	a = (unsigned char)c;
	while (n-- > 0)
	{
		if (*m++ == a)
			return (m - 1);
	}
	return (NULL);
}
