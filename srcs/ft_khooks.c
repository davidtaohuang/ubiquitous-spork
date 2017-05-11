/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_khooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 19:53:06 by dhuang            #+#    #+#             */
/*   Updated: 2017/04/17 19:53:06 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
**	Key 257 = shift, locks point for julia
**	Key 53 	= escape, exits program
**	Key 125	= down arrow, zooms out
**	Key 126	= up arrow, zooms in
**	Key 123 = left
**	Key 124 = right
**	Key 6	= z, zoom reset
**	Key 78	= - from numpad, decreases maximum iterations for escape calcs
**	Key 69	= + from numpad, increases maximum iterations for escape calcs
**	Key 27	= alphanumeric -, decreases maximum iterations for escape calcs
**	Key 24	= alphanumeric +, increases maximum iterations for escape calcs
*/

void	ft_keyexit(t_mlxdata *d)
{
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->win);
	ft_freemlxdata(d);
	exit(1);
}

int        exit_hook(int key, t_mlxdata *d)
{
    (void)key;
    (void)d;
	exit(1);
    return (0);
}

void	ft_keyrot(int key, t_mlxdata *d)
{
	if (key == 124)
		d->right = 1;
	if (key == 123)
		d->left = 1;
}

void	ft_keymove(int key, t_mlxdata *d)
{
	if (key == 126)
		d->up = 1;
	if (key == 125)
		d->down = 1;
}

int		ft_kdown(int key, t_mlxdata *d)
{
	ft_printf("Key = %d\n", key);
	if (key == 48)
	{
		d->info = (!(d->info) ? 1 : 0);
		ft_mlxredraw(d);
	}
	if (key >= 123 && key <= 124)
		ft_keyrot(key, d);
	if (key >= 125 && key <= 126)
		ft_keymove(key, d);
	if (key == 6)
		d->shift = 1;
	if (key == 53)
		ft_keyexit(d);
	return (0);
}

int		ft_kup(int key, t_mlxdata *d)
{
	if (key == 126)
		d->up = 0;
	if (key == 125)
		d->down = 0;
	if (key == 123)
		d->left = 0;
	if (key == 124)
		d->right = 0;
	if (key == 6)
		d->shift = 0;
	return (0);
}
