/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatdbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:51:57 by dhuang            #+#    #+#             */
/*   Updated: 2017/02/06 16:51:57 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../includes/ft_printf.h"

char		*makeinfnan(double n)
{
	char	*num;

	num = ft_strnew(3);
	if (isinf(n))
		ft_strcpy(num, "inf");
	else
		ft_strcpy(num, "NaN");
	if (signbit(n))
		num = ft_strjoin("-", num);
	return (num);
}

static char	*makedbl(t_format *flags)
{
	double		n;
	char		*str;
	char		*frac;
	char		lastdig;
	int			len;

	n = *(double*)ARG;
	str = ft_itoa((long long)n);
	len = ft_strlen(str);
	if (*(long long*)ARG < 0)
		n *= -1;
	frac = ft_strnew(P);
	lastdig = ft_dtoa(n, P, frac);
	str = ft_strjoinreplace(str, frac);
	ft_memdel((void**)&frac);
	if (lastdig > 4)
	{
		if (rounding(str, ft_strlen(str) - 1))
		{
			str = adddigit(str);
			len++;
		}
	}
	P = len;
	return (str);
}

char		*adddecpt(char *dec, int len)
{
	char	*tmp;
	int		i;
	int		newlen;

	newlen = ft_strlen(dec);
	tmp = ft_strnew(newlen + 1);
	i = 0;
	while (i < len)
	{
		tmp[i] = dec[i];
		i++;
	}
	tmp[i] = '.';
	while (i < newlen)
	{
		tmp[i + 1] = dec[i];
		i++;
	}
	ft_memdel((void**)&dec);
	return (tmp);
}

void		formatdbl(t_format *flags)
{
	char	*str;

	if (isinf(*(double*)ARG) || isnan(*(double*)ARG))
	{
		str = makeinfnan(*(double*)ARG);
		P = -1;
	}
	else
	{
		if (LEN == 3)
			str = makedbl(flags);
		else
			str = makedbl(flags);
		str = adddecpt(str, P);
	}
	ft_memdel((void**)&ARG);
	ARG = str;
	FBLEN = ft_strlen(ARG);
}
