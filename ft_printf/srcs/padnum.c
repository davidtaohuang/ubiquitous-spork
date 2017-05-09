/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padnum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:06:03 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/31 18:06:03 by dhuang           ###   ########.fr       */
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

static char	*padsign(t_format *flags)
{
	char	*sign;
	char	*tmp;

	sign = ft_strnew(1);
	if (FGP)
		sign[0] = '+';
	else if (FGS)
		sign[0] = ' ';
	if (SA == '-')
	{
		sign[0] = '-';
		tmp = ft_strsub(ARG, 1, FBLEN - 1);
		ft_memdel((void**)&ARG);
		ARG = tmp;
		FBLEN--;
	}
	return (sign);
}

static void	subzero(t_format *flags)
{
	char	*tmp;

	if (FBLEN == 1 && P != -1 && *((char*)ARG) == '0')
	{
		*((char*)ARG) = 0;
		FBLEN = 0;
	}
	if (P > FBLEN)
	{
		tmp = ft_strnew(P - FBLEN);
		ft_memset(tmp, '0', P - FBLEN);
		tmp = ft_strjoinreplace(tmp, ARG);
		ft_memdel((void**)&ARG);
		ARG = tmp;
		FBLEN = P;
	}
}

void		padnum(t_format *flags)
{
	char	*s;
	char	*space;

	s = padsign(flags);
	subzero(flags);
	if (W > FBLEN + (s[0] ? 1 : 0))
	{
		space = ft_strnew(W - FBLEN - (s[0] ? 1 : 0));
		if (FGZ && P <= flags->negp)
			ft_memset(space, '0', W - FBLEN - (s[0] ? 1 : 0));
		else
			ft_memset(space, ' ', W - FBLEN - (s[0] ? 1 : 0));
		if (FGZ && P <= 1)
			ARG = stitch3(s, space, ARG);
		else
		{
			if (FGM)
				ARG = stitch3(s, ARG, space);
			else
				ARG = stitch3(space, s, ARG);
		}
	}
	else
		ARG = stitch2(s, ARG);
	FBLEN = ft_strlen(ARG);
}
