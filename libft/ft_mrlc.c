/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mrlc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 20:45:33 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:53:33 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

void	*ft_mrlc(void *mem, size_t old, size_t new)
{
	void	*m;

	m = ft_memalloc(new);
	if (!m)
		return (NULL);
	ft_memmove(m, mem, old);
	free(mem);
	return (m);
}
