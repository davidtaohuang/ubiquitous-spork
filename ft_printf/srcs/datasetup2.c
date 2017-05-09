/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datasetup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 19:05:40 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/22 19:05:40 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	findhhll(t_format *flags, char *tmp, int len, int i)
{
	if (tmp[i] == 'h')
	{
		if (i < len - 1 && tmp[i + 1] == 'h')
		{
			flags->length = -2;
			return (i + 1);
		}
		else
			flags->length = -1;
	}
	else
	{
		if (i < len - 1 && tmp[i + 1] == 'l')
		{
			flags->length = 2;
			return (i + 1);
		}
		else
			flags->length = 1;
	}
	return (i);
}

void		findlength(t_format *flags, char *tmp, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (tmp[i] == 'h' && flags->length <= 0)
			i = findhhll(flags, tmp, len, i);
		else if (tmp[i] == 'l')
			i = findhhll(flags, tmp, len, i);
		else if (tmp[i] == 'L')
			flags->length = 3;
		else if (tmp[i] == 'j')
			flags->length = 4;
		else if (tmp[i] == 'z')
			flags->length = 5;
		else if (tmp[i] == 't')
			flags->length = 6;
		i++;
	}
}

static void	assignast(t_format *flags, va_list *args, int i, int w)
{
	int		arg;

	arg = va_arg(*args, int);
	if (w && (!(flags->wl) || i > flags->wl))
		flags->width = arg;
	else if (!w && (!(flags->pl) || i > flags->pl))
		flags->precision = arg;
}

void		findast(t_format *flags, char *tmp, int len, va_list *args)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (tmp[i] == '*')
		{
			if (i > 0 && tmp[i - 1] == '.')
			{
				assignast(flags, args, i, 0);
				if (flags->precision < 0)
				{
					flags->negp = 1;
					flags->precision = 1;
				}
			}
			else
				assignast(flags, args, i, 1);
			i++;
		}
		else
			i++;
	}
}
