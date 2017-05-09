/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padhex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 23:53:01 by dhuang            #+#    #+#             */
/*   Updated: 2017/02/08 23:53:01 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**	FGP = flags->flagplus
**	FGS = flags->flagspace
**	FGN = flags->flagpound
**	FGM = flags->flagminus
**	FGZ = flags->flagzero
*/

static char	*padhexwid(t_format *flags)
{
	char	*tmp;
	char	*ox;

	ox = ft_strnew(2);
	ox[0] = '0';
	ox[1] = (TYPE == 'p' ? 'x' : TYPE);
	if (P > FBLEN)
	{
		tmp = ft_strnew(P - FBLEN);
		ft_memset(tmp, '0', P - FBLEN);
		tmp = ft_strjoinreplace(tmp, ARG);
		ft_memdel((void**)&ARG);
		ARG = tmp;
		FBLEN = P;
	}
	return (ox);
}

static void	subzero(t_format *flags)
{
	if (FBLEN == 1 && P != -1 && P != 1 && *((char*)ARG) == '0')
	{
		*((char*)ARG) = 0;
		FBLEN = 0;
	}
}

void		padhex(t_format *flags)
{
	char	*ox;
	char	*space;

	ox = padhexwid(flags);
	subzero(flags);
	if (W > FBLEN + 2)
	{
		space = ft_strnew(W - FBLEN - 2);
		ft_memset(space, ((FGZ && P <= 1) ? '0' : ' '), W - FBLEN - 2);
		if (FGZ && P <= 1)
			ARG = stitch3(ox, space, ARG);
		else
		{
			if (FGM)
				ARG = stitch3(ox, ARG, space);
			else
				ARG = stitch3(space, ox, ARG);
		}
	}
	else
		ARG = stitch2(ox, ARG);
	FBLEN = ft_strlen(ARG);
}
