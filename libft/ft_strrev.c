/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 23:02:51 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/24 10:57:29 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	if (str)
	{
		i = 0;
		j = ft_strlen(str) - 1;
		while (j > i)
		{
			tmp = str[i];
			str[i++] = str[j];
			str[j--] = tmp;
		}
	}
}
