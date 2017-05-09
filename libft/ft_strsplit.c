/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 17:22:39 by dhuang            #+#    #+#             */
/*   Updated: 2016/10/27 19:56:39 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

static int	ft_wordcount(char *old, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (old[i])
	{
		if (old[i] != c && (old[i + 1] == c || old[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	ft_lengths(char **array, char *old, char c)
{
	int		i;
	int		words;
	int		length;

	i = 0;
	words = 0;
	length = 0;
	while (old[i])
	{
		if (old[i] != c)
			length++;
		if (i > 0)
		{
			if (old[i] == c && old[i - 1] != c)
			{
				array[words++] = ft_strnew(length);
				length = 0;
			}
		}
		i++;
	}
	if (old[i - 1] != c)
		array[words] = ft_strnew(length);
}

static void	ft_makewords(char **array, char *old, char c)
{
	int		i;
	int		words;
	int		length;

	i = 0;
	words = 0;
	length = 0;
	while (old[i])
	{
		if (old[i] != c)
		{
			array[words][length] = old[i];
			length++;
		}
		if (i > 0)
		{
			if (old[i] == c && old[i - 1] != c)
			{
				length = 0;
				words++;
			}
		}
		i++;
	}
}

static int	ft_malloccheck(char **array, int words)
{
	int		i;

	i = 0;
	while (i < words)
	{
		if (!array[i++])
		{
			i = 0;
			while (i < words)
				free(array[i++]);
			free(array);
			return (0);
		}
	}
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	char	*old;
	int		words;

	old = (char*)s;
	words = ft_wordcount(old, c);
	array = (char**)malloc(sizeof(char*) * (words + 1));
	if (!array)
		return (array);
	array[words] = 0;
	if (!words)
		return (array);
	ft_lengths(array, old, c);
	if (!ft_malloccheck(array, words))
		return (NULL);
	ft_makewords(array, old, c);
	return (array);
}
