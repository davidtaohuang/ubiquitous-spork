/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 20:23:00 by dhuang            #+#    #+#             */
/*   Updated: 2017/04/24 20:23:00 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		shade(t_col *c, int a, int b)
{
	double	ratio;

	ratio = (double)a / b;
	c->rgb[0] = (unsigned char)(c->rgb[0] * ratio);
	c->rgb[1] = (unsigned char)(c->rgb[1] * ratio);
	c->rgb[2] = (unsigned char)(c->rgb[2] * ratio);
	c->rgb[3] = (unsigned char)(c->rgb[3] * ratio);
}

void		maketex(t_mlxdata *d, char *str, t_tex **tex)
{
	t_tex	*tmp;

	tmp = (t_tex*)ft_memalloc(sizeof(t_tex));
	tmp->img = mlx_xpm_file_to_image(d->mlx, str, &tmp->w, &tmp->h);
	tmp->imgd = (unsigned int*)mlx_get_data_addr(tmp->img, &tmp->bbp,
		&tmp->line, &tmp->endian);
	*tex = tmp;
}

void		maketextures(t_mlxdata *d)
{
	maketex(d, "textures/sea_lantern.xpm", &d->ftex);
	maketex(d, "textures/ice.xpm", &d->ctex);
	maketex(d, "textures/obsidian.xpm", &d->wtex);
}

char		**makemap(int x, int y)
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
