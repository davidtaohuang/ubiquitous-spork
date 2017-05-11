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

int		main(int ac, char **av)
{
	t_mlxdata	*d;

	if (ac == 2)
	{
		d = ft_getmap(av[1]);
		if (d)
		{
			threadmanage(d);
			mlx_do_key_autorepeatoff(d->mlx);
			mlx_hook(d->win, 2, 1, ft_kdown, d);
			mlx_hook(d->win, 3, 1, ft_kup, d);
			mlx_hook(d->win, 17, 0, exit_hook, d);
			mlx_loop_hook(d->mlx, ft_redraw, d);
			mlx_loop(d->mlx);
		}
	}
	else
		ft_puterror(1);
	return (0);
}
