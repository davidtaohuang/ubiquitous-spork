/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 17:13:20 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:57:08 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

char	**ft_strnew2(size_t size)
{
	char	**m;

	m = (char**)ft_memalloc(sizeof(char*) * (size + 1));
	return (m);
}
