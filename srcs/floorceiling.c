/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:53:34 by dhuang            #+#    #+#             */
/*   Updated: 2017/05/01 21:53:34 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_vec	fwallsetup(t_calcs *c, int side)
{
	t_vec	fwall;

	if (!side && c->raydir.x > 0)
	{
		fwall.x = c->map.x;
		fwall.y = c->map.y + c->wallx;
	}
	else if (!side && c->raydir.x < 0)
	{
		fwall.x = c->map.x + 1.0;
		fwall.y = c->map.y + c->wallx;
	}
	else if (side && c->raydir.y > 0)
	{
		fwall.x = c->map.x + c->wallx;
		fwall.y = c->map.y;
	}
	else
	{
		fwall.x = c->map.x + c->wallx;
		fwall.y = c->map.y + 1.0;
	}
	return (fwall);
}

void	fccalc(t_mlxdata *d, t_calcs *c, int j, int i)
{
	double	cdist;
	double	weight;
	t_vec	cfloor;
	t_vec	tex;
	t_col	color;

	cdist = WINY / ((double)2.0 * j - WINY);
	weight = cdist / c->wall;
	cfloor.x = weight * c->fwall.x + (1.0 - weight) * d->pos.x;
	cfloor.y = weight * c->fwall.y + (1.0 - weight) * d->pos.y;
	tex.x = (int)(cfloor.x * d->ctex->w) % (int)d->ctex->w;
	tex.y = (int)(cfloor.y * d->ctex->w) % (int)d->ctex->w;
	color.c = d->ctex->imgd[(int)d->ctex->w * (int)tex.y + (int)tex.x];
	*(d->imgd + (WINY - j) * WINX + i) = color.c;
	tex.x = (int)(cfloor.x * d->ftex->w) % (int)d->ftex->w;
	tex.y = (int)(cfloor.y * d->ftex->h) % (int)d->ftex->h;
	color.c = d->ftex->imgd[d->ftex->w * (int)tex.y + (int)tex.x];
	*(d->imgd + j * WINX + i) = color.c;
}

void	drawfc(t_mlxdata *d, t_calcs *c, int drawend, int i)
{
	int		j;

	c->fwall = fwallsetup(c, c->wside);
	if (drawend < 0)
		drawend = WINY - 1;
	j = drawend + 1;
	while (j < WINY)
	{
		fccalc(d, c, j, i);
		j++;
	}
}
