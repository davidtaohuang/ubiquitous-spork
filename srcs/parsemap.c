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

size_t	ft_arrlen(char **s)
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

t_vec		ft_getmeta(int fd, int x, int y)
{
	char	*line;
	char	**tmp;
	t_vec	vec;
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

char	**makemap(int x, int y)
{
	int		i;
	char	**tmp;

	tmp = (char**)ft_memalloc(sizeof(char*) * y);
	i = 0;
	while (i < y)
	{
		tmp[i] = ft_strnew(x);
		i++;
	}
	return (tmp);
}

/*
**	d->dir.y = 0;
**	d->odir.y = 0;
**	d->plane.x = 0;
**	d->oplane.x = 0;
**
**	d->bbp = BBP;
**	d->line = LINE;
**	d->endian = ENDIAN;
*/

t_mlxdata	*mlxsetup(t_vec size, t_vec start)
{
	t_mlxdata	*d;

	d = (t_mlxdata*)ft_memalloc(sizeof(t_mlxdata));
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WINX, WINY, "wolf3d");
	d->img = mlx_new_image(d->mlx, WINX, WINY);
	d->imgd = (unsigned int*)mlx_get_data_addr(d->img, &(d->bbp), &(d->line),
		&(d->endian));
	d->pos.x = start.x;
	d->pos.y = start.y;
	d->dir.x = -1;
	d->odir.x = -1;
	d->plane.y = 0.66;
	d->oplane.y = 0.66;
	d->mapsize.x = (int)size.x;
	d->mapsize.y = (int)size.y;
	d->wmap = makemap((int)size.x, (int)size.y);
	maketextures(d);
	return (d);
}

int		checkmap(t_mlxdata *d)
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

void		loadmap(t_mlxdata *d, int fd)
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

t_mlxdata	*ft_getmap(char *file)
{
	int			fd;
	t_mlxdata	*d;
	t_vec		size;
	t_vec		start;

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
