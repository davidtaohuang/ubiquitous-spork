/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:50:38 by dhuang            #+#    #+#             */
/*   Updated: 2017/04/17 16:50:38 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

#define mapWidth 24
#define mapHeight 24

int		hitcalc(t_mlxdata *d, t_vec step, int hit)
{
	int		side;
	
	while (!hit)
	{
		if (d->side.x < d->side.y)
		{
			d->side.x += d->delta.x;
			d->map.x += step.x;
			side = 0;
		}
		else
		{
			d->side.y += d->delta.y;
			d->map.y += step.y;
			side = 1;
		}
		if (d->wmap[(int)d->map.x][(int)d->map.y] > 0)
			hit = 1;
	}
	if (!side)
		d->wall = (d->map.x - d->raypos.x + (1 - step.x) / 2) / d->raydir.x;
	else
		d->wall = (d->map.y - d->raypos.y + (1 - step.y) / 2) / d->raydir.y;
	return (side);
}

int		stepcalc(t_mlxdata *d)
{
	t_vec	step;

	if (d->raydir.x < 0)
	{
		step.x = -1;
		d->side.x = (d->raypos.x - d->map.x) * d->delta.x;
	}
	else
	{
		step.x = 1;
		d->side.x = (d->map.x + 1.0 - d->raypos.x) * d->delta.x;
	}
	if (d->raydir.y < 0)
	{
		step.y = -1;
		d->side.y = (d->raypos.y - d->map.y) * d->delta.y;
	}
	else
	{
		step.y = 1;
		d->side.y = (d->map.y + 1.0 - d->raypos.y) * d->delta.y;
	}
	return (hitcalc(d, step, 0));
}

void	shade(t_col *c, int a, int b)
{
	double	ratio;

	ratio = (double)a / b;
	c->rgb[0] = (unsigned char)(c->rgb[0] * ratio);
	c->rgb[1] = (unsigned char)(c->rgb[1] * ratio);
	c->rgb[2] = (unsigned char)(c->rgb[2] * ratio);
	c->rgb[3] = (unsigned char)(c->rgb[3] * ratio);
}

void	draw(t_mlxdata *d, int side, int i)
{
	int		lineheight;
	int 	drawstart;
	int 	drawend;
	t_col	color;
	int		j;
	
	lineheight = (int)(WINY / d->wall);
	drawstart = (int)(-(double)lineheight / 2 + WINY / 2);
	if (drawstart < 0)
		drawstart = 0;
	drawend = (int)((double)lineheight / 2 + WINY / 2);
	if (drawend >= WINY)
		drawend = WINY - 1;
	// ft_printf("WALLX, %d\n", i);

	if (!side)
		d->wallx = d->raypos.y + d->wall * d->raydir.y;
	else
		d->wallx = d->raypos.x + d->wall * d->raydir.x;
	d->wallx -= (int)d->wallx;

	int texx = (int)(d->wallx * (double)TW);
	if ((!side && d->raydir.x > 0) || (side && d->raydir.y < 0))
		texx = TW - texx - 1;

	// color.c = 0x00FF0000;

	j = drawstart;
	while (j <= drawend)
	{
		// int g = j * 256 + (lineheight - WINY) * 128;
		int texy = (((j * 256 + (lineheight - WINY) * 128) * TH) / lineheight) / 256;
		color.c = d->wtex->imgd[TW * texy + texx];
		if (side)
			shade(&color, 1, 2);	
		*(d->imgd + j * WINX + i) = color.c;
		j++;
	}
	drawfc(d, side, drawend, i);
}

static void	mlxputinfo(t_mlxdata *d)
{
	char		*str;

	ft_asprintf(&str, "X = %.2f Y = %.2f", d->pos.x, d->pos.y);
	mlx_string_put(d->mlx, d->win, 0, 0, 0x00FFFFFF, str);
	free(str);
}

#define CCEIL 0x00bebebe
#define CFLOOR 0x00696969

// void	floorceiling(t_mlxdata *d)
// {
// 	int		half;
// 	int		all;
// 	int		i;

// 	all = WINX * WINY;
// 	half = all / 2;
// 	i = 0;
// 	while (i < half)
// 		*(d->imgd + i++) = CCEIL;
// 	while (i < all)
// 		*(d->imgd + i++) = CFLOOR;
// }

void	raycaster(t_mlxdata *d)
{
	int		side;
	int		i;
	
	// floorceiling(d);
	i = 0;
	while (i < WINX)
	{
		d->camx = 2 * i / (double)WINX - 1;
		d->raypos.x = d->pos.x;
		d->raypos.y = d->pos.y;
		d->raydir.x = d->dir.x + d->plane.x * d->camx;
		d->raydir.y = d->dir.y + d->plane.y * d->camx;
		d->map.x = (int)d->raypos.x;
		d->map.y = (int)d->raypos.y;
		d->delta.x = sqrt(1 + (d->raydir.y * d->raydir.y) / (d->raydir.x * d->raydir.x));
		d->delta.y = sqrt(1 + (d->raydir.x * d->raydir.x) / (d->raydir.y * d->raydir.y));
		side = stepcalc(d);
		draw(d, side, i);
		i++;
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	mlxputinfo(d);
}

#define CBUF 1.1
#define CBUF2 0.05

void	collision(t_mlxdata *d, t_vec move, int neg)
{
	t_vec	new;

	new.x = d->pos.x + (neg ? -move.x : move.x) * MSPD;
	new.y = d->pos.y + (neg ? -move.y : move.y) * MSPD;
	if (new.x < CBUF)
		new.x = CBUF;
	if (new.y < CBUF)
		new.y = CBUF;
	if (new.x > d->mapsize.x - CBUF)
		new.x = d->mapsize.x - CBUF;
	if (new.y > d->mapsize.y - CBUF)
		new.y = d->mapsize.y - CBUF;
	if (!d->wmap[(int)(new.x - CBUF2)][(int)(d->pos.y)] && !d->wmap[(int)(new.x + CBUF2)][(int)(d->pos.y)])
		d->pos.x = new.x;
	if (!d->wmap[(int)(d->pos.x)][(int)(new.y - CBUF2)] && !d->wmap[(int)(d->pos.x)][(int)(new.y + CBUF2)])
		d->pos.y = new.y;
}

int		ft_redraw(t_mlxdata *d)
{
	if (d->updown == 1)
	{
		collision(d, d->dir, 0);
		// if (!(d->wmap[(int)(d->pos.x + d->dir.x * MSPD)][(int)(d->pos.y)]))
		// 	d->pos.x += d->dir.x * MSPD;
		// if (!(d->wmap[(int)(d->pos.x)][(int)(d->pos.y + d->dir.y * MSPD)]))
		// 	d->pos.y += d->dir.y * MSPD;
	}
	if (d->updown == 2)
	{
		collision(d, d->dir, 1);
		// if (!(d->wmap[(int)(d->pos.x - d->dir.x * MSPD)][(int)(d->pos.y)]))
		// 	d->pos.x -= d->dir.x * MSPD;
		// if (!(d->wmap[(int)(d->pos.x)][(int)(d->pos.y - d->dir.y * MSPD)]))
		// 	d->pos.y -= d->dir.y * MSPD;
	}
	// if (d->pos.x <= 1)
	// 	d->pos.x += MSPD;
	// if (d->pos.y <= 1)
	// 	d->pos.y += MSPD;

	if (d->leftright == 1 && d->shift)
	{
		collision(d, d->plane, 0);
		// if (!(d->wmap[(int)(d->pos.x + d->plane.x * MSPD)][(int)(d->pos.y)]))
		// 	d->pos.x += d->plane.x * MSPD;
		// if (!(d->wmap[(int)(d->pos.x)][(int)(d->pos.y + d->plane.y * MSPD)]))
		// 	d->pos.y += d->plane.y * MSPD;
	}
	if (d->leftright == 2 && d->shift)
	{
		collision(d, d->plane, 1);
		// if (!(d->wmap[(int)(d->pos.x - d->plane.x * MSPD)][(int)(d->pos.y)]))
		// 	d->pos.x -= d->plane.x * MSPD;
		// if (!(d->wmap[(int)(d->pos.x)][(int)(d->pos.y - d->plane.y * MSPD)]))
		// 	d->pos.y -= d->plane.y * MSPD;
	}

	if (d->leftright == 1 && !d->shift)
		d->angle -= RSPD;
	if (d->leftright == 2 && !d->shift)
		d->angle += RSPD;
	if (d->angle >= 360)
		d->angle -= 360;
	if (d->angle < 0)
		d->angle += 360;
	d->dir.x = d->odir.x * cos(RA) - d->odir.y * sin(RA);
	d->dir.y = d->odir.x * sin(RA) + d->odir.y * cos(RA);
	d->plane.x = d->oplane.x * cos(RA) - d->oplane.y * sin(RA);
	d->plane.y = d->oplane.x * sin(RA) + d->oplane.y * cos(RA);

	if (d->leftright || d->updown)
	{
		mlx_clear_window(d->mlx, d->win);
		mlx_destroy_image(d->mlx, d->img);
		d->img = mlx_new_image(d->mlx, WINX, WINY);
		d->imgd = (unsigned int*)mlx_get_data_addr(d->img, &(d->bbp), &(d->line), &(d->endian));
		raycaster(d);
	}
	return (1);
}

int		main(int ac, char ** av)
{
	t_mlxdata	*d;

	if (ac == 2)
	{
		d = ft_getmap(av[1]);
		if (d)
		{
			raycaster(d);
			mlx_do_key_autorepeatoff(d->mlx);
			mlx_hook(d->win, 2, 1, ft_kdown, d);
			mlx_hook(d->win, 3, 1, ft_kup, d);
			// mlx_hook(d->win, 6, 1, ft_mmove, (void*)d);
			// mlx_hook(d->win, 5, 1, ft_mup, (void*)d);
			// mlx_hook(d->win, 4, 1, ft_mdown, (void*)d);
			mlx_hook(d->win, 17, 0, exit_hook, d);
			mlx_loop_hook(d->mlx, ft_redraw, d);
			mlx_loop(d->mlx);
		}
	}
	else
		ft_puterror(1);
	return (0);
}
