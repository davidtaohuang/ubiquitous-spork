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

/*
**	This file includes the portion of the raycasting loop responsible for
**	drawing drawing ceiling and floor pixels to the screen.
**
**	1.	fwall = the exact position of where the vertical stripe where the ray
**		contacts the wall meets the floor and ceiling based on whether a
**		horizontal or vertical side is hit by the ray and the direction of
**		the ray
**	2.	drawend = the last pixel drawn of the wall; now used as the start of
**		the floor and ceiling
**	3.	cdist = current y pixel in screen normalized to range between -1 and 1
**	4.	weight = current y pixel as proportion of distance between player and
**		ceiling/floor
**	5.	cfloor = coordinates of floor/ceiling tile between player and wall
**	6.	tex = coordinates within the floor/ceiling texture of the specific
**		floor/ceiling tile
*/

static t_vec	fwallsetup(t_calcs *c, int side)
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

static void		fccalc(t_mlxdata *d, t_calcs *c, int j, int i)
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
	shade(&color, 1, 2);
	*(d->imgd + (WINY - j) * WINX + i) = color.c;
	tex.x = (int)(cfloor.x * d->ftex->w) % (int)d->ftex->w;
	tex.y = (int)(cfloor.y * d->ftex->h) % (int)d->ftex->h;
	color.c = d->ftex->imgd[d->ftex->w * (int)tex.y + (int)tex.x];
	shade(&color, 1, 2);
	*(d->imgd + j * WINX + i) = color.c;
}

void			drawfc(t_mlxdata *d, t_calcs *c, int drawend, int i)
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
