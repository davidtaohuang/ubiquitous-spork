/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 22:34:44 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 11:00:12 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*s;
	size_t	i;

	s = s1;
	while (*s)
		s++;
	i = 0;
	while (*s2 && i++ < n)
		*s++ = *s2++;
	*s = '\0';
	return (s1);
}