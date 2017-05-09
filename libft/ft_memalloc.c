/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:21:41 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:52:40 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

void	*ft_memalloc(size_t size)
{
	void	*m;
	void	*tmp;

	m = (void *)malloc(size);
	if (!m)
		return (NULL);
	tmp = m;
	while (size-- > 0)
		*(unsigned char*)tmp++ = 0;
	return (m);
}
