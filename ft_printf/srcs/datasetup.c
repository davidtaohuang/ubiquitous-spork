/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datasetup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:39:59 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/24 18:39:59 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*g_numconv = "diouxXDOUeEfFgGaAp";

static void	findw(t_format *flags, char *tmp, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (ft_isdigit(tmp[i]) && tmp[i] != '0')
		{
			if (tmp[i - 1] != '.')
			{
				flags->width = ft_atoi(tmp + i);
				flags->wl = i;
			}
			while (ft_isdigit(tmp[i]))
				i++;
		}
		else
			i++;
	}
}

static void	findp(t_format *flags, char *tmp, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (tmp[i] == '.')
		{
			flags->precision = 0;
			while (!ft_isdigit(tmp[i]) && i < len)
				i++;
			if (ft_isdigit(tmp[i]))
			{
				flags->precision = ft_atoi(tmp + i);
				flags->pl = i;
				while (ft_isdigit(tmp[i]))
					i++;
			}
		}
		else
			i++;
	}
}

/*
** 1. Either '+' or ' ' but not both.
*/

static void	findflags(t_format *flags, char *tmp, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (tmp[i] == '-')
			flags->flagminus = 1;
		else if (tmp[i] == '+')
			flags->flagplus = 1;
		else if (tmp[i] == ' ')
			flags->flagspace = 1;
		else if (tmp[i] == '0' && tmp[i - 1] != '.' && !ft_isdigit(tmp[i - 1]))
			flags->flagzero = 1;
		else if (tmp[i] == '#')
			flags->flagpound = 1;
		i++;
	}
}

void		datasetup(t_format *flags, char *format, va_list *args)
{
	int		len;
	char	*tmp;

	tmp = format;
	tmp++;
	flags->precision = -1;
	len = ft_strchr(tmp, flags->conversion) - tmp;
	findflags(flags, tmp, len);
	findw(flags, tmp, len);
	findp(flags, tmp, len);
	findast(flags, tmp, len, args);
	if (flags->width < 0)
	{
		flags->width *= -1;
		flags->flagminus = 1;
	}
	if (flags->flagminus || (!P && ft_strchr(g_numconv, flags->conversion)))
		flags->flagzero = 0;
	if (flags->flagplus)
		flags->flagspace = 0;
	findlength(flags, tmp, len);
}
