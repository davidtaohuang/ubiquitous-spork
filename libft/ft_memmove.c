/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 22:20:01 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:53:14 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*m;
	unsigned char	*old;

	m = (unsigned char*)dst;
	old = (unsigned char*)src;
	if (src > dst)
	{
		while (n-- > 0)
			*m++ = *old++;
	}
	else
	{
		m += n;
		old += n;
		while (n-- > 0)
			*--m = *--old;
	}
	return (dst);
}
