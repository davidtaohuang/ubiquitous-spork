/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 13:41:58 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:52:58 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*m1;
	unsigned char	*m2;

	m1 = (unsigned char*)s1;
	m2 = (unsigned char*)s2;
	while (n-- > 0)
	{
		if (*m1++ != *m2++)
			return ((int)(*(m1 - 1) - *(m2 - 1)));
	}
	return (0);
}
