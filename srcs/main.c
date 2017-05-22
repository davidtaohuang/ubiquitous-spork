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

/*
**	Main verifies that a map file has been passed as argument and otherwise
**	outputs the correct usage to STD_ERROR. It then attempts to parse the map
**	and sets up the MLX environment. After the first frame is rendered in the
**	window, the instructions are put to the screen and loop/hook functions
**	are started.
*/

void	instructions(void)
{
	ft_printf("W or UP ARROW to move forward\n");
	ft_printf("S or DOWN ARROW to move backwards\n");
	ft_printf("A or LEFT ARROW to turn to the left\n");
	ft_printf("D or RIGHT ARROW to turn to the right\n\n");
	ft_printf("Hold SHIFT to sprint (move faster)\n");
	ft_printf("Hold LEFT-CONTROL or SPACE to walk (move slower)\n");
	ft_printf("Hold Z and A/LEFT ARROW or D/RIGHT ARROW to strafe left/right");
	ft_printf("\n\nPress TAB to display debug info\n");
	ft_printf("Press ESCAPE to exit the program\n");
}

int		main(int ac, char **av)
{
	t_mlxdata	*d;

	if (ac == 2)
	{
		d = ft_getmap(av[1]);
		if (d)
		{
			threadmanage(d);
			instructions();
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
