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

/*
**	Shade is shading funciton that modifies the RGB values associated with the
**	color stored in a struct of type t_col.
*/

void		shade(t_col *c, int a, int b)
{
	double	ratio;

	ratio = (double)a / b;
	c->rgb[0] = (unsigned char)(c->rgb[0] * ratio);
	c->rgb[1] = (unsigned char)(c->rgb[1] * ratio);
	c->rgb[2] = (unsigned char)(c->rgb[2] * ratio);
	c->rgb[3] = (unsigned char)(c->rgb[3] * ratio);
}

/*
**	maketex allocates memory for a t_tex struct and then uses to
**	mlx_xpm_file_to_image function to load a texture into memory;
*/

static void	maketex(t_mlxdata *d, char *str, t_tex **tex)
{
	t_tex	*tmp;

	tmp = (t_tex*)ft_memalloc(sizeof(t_tex));
	tmp->img = mlx_xpm_file_to_image(d->mlx, str, &tmp->w, &tmp->h);
	tmp->imgd = (unsigned int*)mlx_get_data_addr(tmp->img, &tmp->bbp,
		&tmp->line, &tmp->endian);
	*tex = tmp;
}

/*
**	maketextures loads specific textures.
*/

static void	maketextures(t_mlxdata *d)
{
	maketex(d, "textures/sea_lantern.xpm", &d->ftex);
	maketex(d, "textures/ice.xpm", &d->ctex);
	maketex(d, "textures/obsidian.xpm", &d->wtex);
}

/*
**	makemap allocates the memory for the world map.
*/

static char	**makemap(int x, int y)
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
**	mlxsetup allocates memory for and initializes the environment struct.
**	The following lines were removed (since the values should be initialized
**	to zero) to save lines.
**
**	d->dir.y = 0;
**	d->odir.y = 0;
**	d->plane.x = 0;
**	d->oplane.x = 0;
*/

t_mlxdata	*mlxsetup(t_ivec size, t_ivec start)
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
	d->mapsize.x = size.x;
	d->mapsize.y = size.y;
	d->wmap = makemap(size.x, size.y);
	maketextures(d);
	return (d);
}
