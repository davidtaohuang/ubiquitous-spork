/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intsxyz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 19:12:39 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/05 21:49:15 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

static int	ft_pointcount(char *old, char c)
{
	int		i;
	int		points;

	i = 0;
	points = 0;
	while (old[i])
	{
		if (old[i] != c && (old[i + 1] == c || old[i + 1] == '\0'))
			points++;
		i++;
	}
	return (points);
}

static int	ft_malloccheck(int **array, int points)
{
	int		i;

	i = 0;
	while (i < points)
	{
		if (!array[i++])
		{
			i = 0;
			while (i < points)
				free(array[i++]);
			free(array);
			return (NULL);
		}
	}
	return (1);
}

static void	ft_makewords(int **array, char *old, char c, int points)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	while (old[i])
	{
		if (old[i] == '\n')
		{
			y++;
			x = 0;
			i++;
		}
		if (old[i] != c && old[i] != '\n')
		{
			array[points][0] = x++;
			array[points][1] = y;
			array[points++][2] = ft_atoi(&old[i]);
		}
		while (old[i + 1] != c && old[i + 1] != '\n')
			i++;
		i++;
	}
}

int			**ft_intsxyz(char *str, char c)
{
	int		points;
	int		**array;
	int		i;

	if (!(points = ft_pointcount(str, c)))
		return (0);
	array = (int**)ft_memalloc(sizeof(int*) * (points + 1));
	if (!array)
		return (array);
	i = 0;
	while (i < points)
	{
		array[i] = (int*)ft_memalloc(sizeof(int) * 3);
		if (!array[i++])
			return ((int**)ft_malloccheck(array, points));
	}
	ft_makewords(array, str, c, 0);
	return (array);
}
