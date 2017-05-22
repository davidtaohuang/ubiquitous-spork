/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:13:30 by dhuang            #+#    #+#             */
/*   Updated: 2017/05/11 16:13:30 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
**	This file contains the main raycasting function, starting with raycaster
**	at the bottom. Raycaster initializes several variables from the
**	environment and x-index value passed in.
**
**	1.	camx = the vertical pixel stripe on the screen normalized to a value
**		between -1 and 1
**	2.	raypos = the starting position of the ray, taken from the player's
**		current coordinates in the world map
**	3.	raydir = the direction of the ray, calculated from the player's
**		direction and camx
**	4.	map = the map square of the ray's starting position
**	5.	delta = the distance traveled along the ray from one edge of
**		side of the map square to the other in the x or y dimensions,
**		calculated using the Pythagorean theorem and the ray's direction
**	6.	wside = whether a vertical side or horizontal side was first hit
**		by the ray, 0 for horizontal, 1 for vertical
**	7.	wall = the perpendicular distance from the the ray position
**		(player position) to the wall hit, normalized by the corresponding
**		ray direction component (how many ray lengths to the wall)
**	8.	lineheight = height of the wall hit in pixels on the screen,
**		calculated based on height of the window in pixesl and wall
**	9.	draw = "vector" storing the the start and end pixels for drawing,
**		calculated from lineheight and the height of the texture
**	10.	wallx = exact vertical stripe on wall hit by ray, calculated from
**		the wall, ray direction, and player position
**	11.	texhit.x = x-coordinate of the texture hit by ray, calculated from
**		wallx and texture width
**	12.	texhit.y = y-coordinate of texture to display on screen, calculated
**		by mapping texture coordinate to portion of lineheight
**	13.	color = color of the specific texture pixel, which is shaded if
**		vertical side is hit
**
**	After wall texture calculations are finished, ceiling and floor pixels are
**	assigned in drawfc.
*/

int		hitcalc(t_mlxdata *d, t_calcs *c, t_vec step, int hit)
{
	int		side;

	while (!hit)
	{
		if (c->side.x < c->side.y)
		{
			c->side.x += c->delta.x;
			c->map.x += step.x;
			side = 0;
		}
		else
		{
			c->side.y += c->delta.y;
			c->map.y += step.y;
			side = 1;
		}
		if (d->wmap[(int)c->map.y][(int)c->map.x] > 0)
			hit = 1;
	}
	if (!side)
		c->wall = (c->map.x - c->raypos.x + (1 - step.x) / 2) / c->raydir.x;
	else
		c->wall = (c->map.y - c->raypos.y + (1 - step.y) / 2) / c->raydir.y;
	return (side);
}

int		stepcalc(t_mlxdata *d, t_calcs *c)
{
	t_vec	step;

	if (c->raydir.x < 0)
	{
		step.x = -1;
		c->side.x = (c->raypos.x - c->map.x) * c->delta.x;
	}
	else
	{
		step.x = 1;
		c->side.x = (c->map.x + 1.0 - c->raypos.x) * c->delta.x;
	}
	if (c->raydir.y < 0)
	{
		step.y = -1;
		c->side.y = (c->raypos.y - c->map.y) * c->delta.y;
	}
	else
	{
		step.y = 1;
		c->side.y = (c->map.y + 1.0 - c->raypos.y) * c->delta.y;
	}
	return (hitcalc(d, c, step, 0));
}

void	draw(t_mlxdata *d, t_calcs *c, int i)
{
	int		j;

	c->wallx -= (int)c->wallx;
	c->texhit.x = (int)(c->wallx * d->wtex->w);
	if ((!c->wside && c->raydir.x > 0) || (c->wside && c->raydir.y < 0))
		c->texhit.x = d->wtex->w - c->texhit.x - 1;
	j = c->draw.x;
	while (j < c->draw.y)
	{
		c->texhit.y = (((j * 256 + (c->lineheight - WINY) * 128) *
			d->wtex->h) / c->lineheight) / 256;
		if (c->texhit.y < d->wtex->h && c->texhit.y > -1)
			c->color.c = d->wtex->imgd[d->wtex->w * c->texhit.y + c->texhit.x];
		if (c->wside)
			shade(&c->color, 1, 2);
		*(d->imgd + j * WINX + i) = c->color.c;
		j++;
	}
	drawfc(d, c, c->draw.y, i);
}

void	raycaster(t_mlxdata *d, int i)
{
	t_calcs	c;

	ft_bzero(&c, sizeof(&c));
	c.camx = 2 * i / (double)WINX - 1;
	c.raypos.x = d->pos.x;
	c.raypos.y = d->pos.y;
	c.raydir.x = d->dir.x + d->plane.x * c.camx;
	c.raydir.y = d->dir.y + d->plane.y * c.camx;
	c.map.x = (int)c.raypos.x;
	c.map.y = (int)c.raypos.y;
	c.delta.x = sqrt(1 + (c.raydir.y * c.raydir.y) / (c.raydir.x * c.raydir.x));
	c.delta.y = sqrt(1 + (c.raydir.x * c.raydir.x) / (c.raydir.y * c.raydir.y));
	c.wside = stepcalc(d, &c);
	c.lineheight = (int)(WINY / c.wall);
	c.draw.x = (int)(-(double)c.lineheight / 2 + WINY / 2);
	if (c.draw.x < 0)
		c.draw.x = 0;
	c.draw.y = (int)((double)c.lineheight / 2 + WINY / 2);
	if (c.draw.y > WINY)
		c.draw.y = WINY;
	if (!c.wside)
		c.wallx = c.raypos.y + c.wall * c.raydir.y;
	else
		c.wallx = c.raypos.x + c.wall * c.raydir.x;
	draw(d, &c, i);
}
