/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 21:48:19 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:52:47 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*m;
	unsigned char	*old;
	unsigned char	a;

	a = (unsigned char)c;
	m = (unsigned char*)dst;
	old = (unsigned char*)src;
	while (n-- > 0)
	{
		*m++ = *old++;
		if (*(old - 1) == a)
			return (m);
	}
	return (NULL);
}
