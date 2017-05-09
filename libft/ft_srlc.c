/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srlc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 15:33:31 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:54:06 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

char	*ft_srlc(char *str, size_t old, size_t new)
{
	char *m;

	m = ft_strnew(new);
	if (!m)
		return (NULL);
	ft_memmove(m, str, old);
	free(str);
	return (m);
}
