/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:54:19 by dhuang            #+#    #+#             */
/*   Updated: 2017/04/19 15:54:19 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
**	ft_arrlen is a helper function that counts the number of char pointers in
**	in the char double-array.
*/

static size_t	ft_arrlen(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

/*
**	ft_getmeta uses get_next_line to retrieve a metadata line from the map
**	file. These lines represent either the size of the map or the starting
**	position of the player in the map. int x and int y are passed in for
**	error-checking and represent the lower limits for the specific values.
**	A map has to be at least 3 by 3 and the starting position has to be at
**	at least (1, 1).
*/

static t_ivec	ft_getmeta(int fd, int x, int y)
{
	char	*line;
	char	**tmp;
	t_ivec	vec;
	size_t	len;

	if (!(get_next_line(fd, &line)))
		ft_puterror(2);
	tmp = ft_strsplit(line, ' ');
	ft_memdel((void**)&line);
	len = ft_arrlen(tmp);
	if (len != 2)
		ft_linecleanup(tmp);
	vec.x = ft_atoi(tmp[0]);
	vec.y = ft_atoi(tmp[1]);
	if (vec.x < x || vec.y < y)
		ft_linecleanup(tmp);
	return (vec);
}

/*
**	checkmap verifies the integrity of the map file. It checks to make sure
**	that the starting position of the player is within the bounds of the
**	map and also in an empty space. It verifies that the outside edges of the
**	map are walls and that the only values for spaces in the map are 0-9 (this
**	full range is not used by the program in its current state but this does
**	allow for up to nine different wall textures in the future).
*/

static int		checkmap(t_mlxdata *d)
{
	int		i;
	int		j;

	if (d->pos.x >= d->mapsize.x - 1 || d->pos.y >= d->mapsize.y - 1)
		return (1);
	if (d->wmap[(int)d->pos.y][(int)d->pos.x] != 0)
		return (1);
	j = 0;
	while (j < d->mapsize.y)
	{
		i = 0;
		while (i < d->mapsize.x)
		{
			if ((i == 0 || i == d->mapsize.x - 1) && d->wmap[j][i] == 0)
				return (1);
			if ((j == 0 || j == d->mapsize.y - 1) && d->wmap[j][i] == 0)
				return (1);
			if (d->wmap[j][i] < 0 || d->wmap[j][i] > 9)
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

/*
**	loadmap transfers the rest of the map file into memory and verifies that
**	each line matches the width specified by the metadata size and the number
**	of lines matches the height specified by the metadata size.
*/

static void		loadmap(t_mlxdata *d, int fd)
{
	int		i;
	int		j;
	char	*line;
	char	**tmp;

	i = 0;
	while (get_next_line(fd, &line))
	{
		tmp = ft_strsplit(line, ' ');
		ft_memdel((void**)&line);
		j = ft_arrlen(tmp);
		if (j != d->mapsize.x)
			ft_cleanall(d, tmp);
		j = -1;
		while (tmp[++j])
			d->wmap[i][j] = ft_atoi(tmp[j]);
		ft_freetmp(tmp);
		i++;
	}
	if (i != (int)d->mapsize.y || checkmap(d))
	{
		ft_freemlxdata(d);
		ft_puterror(2);
	}
}

/*
**	ft_getmap opens the file, gets the metadata, initializes the MLX
**	environment and then loads the rest of the map if it passes validation.
*/

t_mlxdata		*ft_getmap(char *file)
{
	int			fd;
	t_mlxdata	*d;
	t_ivec		size;
	t_ivec		start;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_puterror(2);
	size = ft_getmeta(fd, 3, 3);
	if (size.x > MAPXMAX || size.y > MAPYMAX)
		ft_puterror(2);
	start = ft_getmeta(fd, 1, 1);
	d = mlxsetup(size, start);
	loadmap(d, fd);
	return (d);
}
