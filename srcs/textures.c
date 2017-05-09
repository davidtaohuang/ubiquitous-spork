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

// #define NH 128
// #define NW 128

// double	*makenoise()
// {
// 	double	*noise;
// 	int		i;

// 	noise = ft_memalloc(sizeof(double) * (NW * NH));
// 	i = 0;
// 	while (i < NW * NH)
// 	{
// 		noise[i] = (rand() % 32768) / (double)32768.0;
// 		i++;
// 	}
// 	return (noise);
// }

// double	smoothnoise(double x, double y, double *noise)
// {
// 	t_vec	frac;
// 	t_vec	v1;
// 	t_vec	v2;
// 	double	value;

// 	frac.x = x - (int)x;
// 	frac.y = y - (int)y;
// 	v1.x = ((int)x + NW - 1) % NW;
// 	v1.y = ((int)y + NH - 1) % NH;
// 	v2.x = ((int)v1.x + NW - 1) % NW;
// 	v2.y = ((int)v1.y + NH - 1) % NH;
// 	value = 0;
// 	value += frac.x * frac.y * noise[(int)v1.y * NW + (int)v1.x];
// 	value += (1 - frac.x) * frac.y * noise[(int)v1.y * NW + (int)v2.x];
// 	value += frac.x * (1 - frac.y) * noise[(int)v2.y * NW + (int)v1.x];
// 	value += (1 - frac.x) * (1 - frac.y) * noise[(int)v2.y * NW + (int)v2.x];
// 	return (value);
// }

// double	turbulence(double x, double y, double size, double *noise)
// {
// 	double	value;
// 	double	initsize;

// 	value = 0;
// 	initsize = size;
// 	while (size >= 1)
// 	{
// 		value += smoothnoise(x / size, y / size, noise) * size;
// 		size /= 2.0;
// 	}
// 	return (128.0 * value / initsize);
// }

// t_col	*maketexture(void)
// {
// 	t_col			*tex;
// 	unsigned int	x;
// 	unsigned int	y;
// 	unsigned int	xc;

// 	tex = (t_col*)ft_memalloc(sizeof(t_col) * TW * TH);
// 	y = 0;
// 	while (y < TH)
// 	{
// 		x = 0;	
// 		while (x < TW)
// 		{
// 			xc = (x * 256 / TW) ^ (y * 256 / TH);
// 			tex[y * TW + x].c = 65793 * xc;
// 			// tex[y * TW + x].c = 65792 * xc;
// 			// tex[y * TW + x].c = 0x00FF0000;
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (tex);
// }

// t_col	*makectex(void)
// {
// 	t_col			*tex;
// 	double			*noise;
// 	unsigned int	x;
// 	unsigned int	y;

// 	noise = makenoise();
// 	tex = (t_col*)ft_memalloc(sizeof(t_col) * TW * TH);
// 	y = 0;
// 	while (y < TH)
// 	{
// 		x = 0;	
// 		while (x < TW)
// 		{
// 			tex[y * TW + x].c = (unsigned int)(sin((double)x / 64 * 2 * M_PI) + sin((double)y / 64 * 2 * M_PI)) * 0x00FFFFFF;
// 			// tex[y * TW + x].c = 0x008080FF;
// 			// tex[y * TW + x].c = 65792 * xc;
// 			// tex[y * TW + x].c = 0x00FF0000;
// 			x++;
// 		}
// 		y++;
// 	}
// 	ft_memdel((void**)&noise);
// 	return (tex);
// }

void	maketex(t_mlxdata *d, char *str, t_tex **tex)
{
	t_tex	*tmp;

	tmp = (t_tex*)ft_memalloc(sizeof(t_tex));
	tmp->img = mlx_xpm_file_to_image(d->mlx, str, &tmp->w, &tmp->h);
	tmp->imgd = (unsigned int*)mlx_get_data_addr(tmp->img, &tmp->bbp, &tmp->line,
		&tmp->endian);
	*tex = tmp;
}

// void	maketextures(t_mlxdata *d)
// {
// 	t_tex	*tmp;

// 	tmp = (t_tex*)ft_memalloc(sizeof(t_tex));
// 	tmp->img = mlx_xpm_file_to_image(d->mlx, "textures/ice.xpm", &tmp->w, &tmp->h);
// 	tmp->imgd = (unsigned int*)mlx_get_data_addr(tmp->img, &tmp->bbp, &tmp->line,
// 		&tmp->endian);
// 	d->ftex = tmp;

// 	tmp = (t_tex*)ft_memalloc(sizeof(t_tex));
// 	tmp->img = mlx_xpm_file_to_image(d->mlx, "textures/bluestone.xpm", &tmp->w, &tmp->h);
// 	tmp->imgd = (unsigned int*)mlx_get_data_addr(tmp->img, &tmp->bbp, &tmp->line,
// 		&tmp->endian);
// 	d->wtex = tmp;

// 	tmp = (t_tex*)ft_memalloc(sizeof(t_tex));
// 	tmp->img = mlx_xpm_file_to_image(d->mlx, "textures/greystone.xpm", &tmp->w, &tmp->h);
// 	tmp->imgd = (unsigned int*)mlx_get_data_addr(tmp->img, &tmp->bbp, &tmp->line,
// 		&tmp->endian);
// 	d->ctex = tmp;
// }

void	maketextures(t_mlxdata *d)
{
	maketex(d, "textures/ice.xpm", &d->ftex);
	maketex(d, "textures/bluestone.xpm", &d->ctex);
	maketex(d, "textures/greystone.xpm", &d->wtex);
}
