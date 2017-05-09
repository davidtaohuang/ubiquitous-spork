/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseswitch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 00:42:18 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/25 00:42:18 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	parsen(t_format *flags, va_list *args, t_data *pf)
{
	flags->arg = va_arg(*args, int*);
	FBLEN = sizeof(int);
	*((int*)flags->arg) = BLEN;
}

void	parsepct(t_format *flags)
{
	flags->arg = ft_strndup(&TYPE, 1);
	FBLEN = 1;
	padgen(flags);
}

void	parseptr(t_format *flags, va_list *args)
{
	flags->arg = (void**)ft_memalloc(sizeof(void*));
	*(void**)((flags->arg)) = va_arg(*args, void*);
	FBLEN = sizeof(void*);
	LEN = 1;
	formatunum(flags);
	padhex(flags);
}

void	parseswitch(t_format *flags, va_list *args, t_data *pf)
{
	if (TYPE == 'p')
		parseptr(flags, args);
	else if (TYPE == 'n')
		parsen(flags, args, pf);
	else if (LEN > 3)
		parsezjt(flags, args, pf);
	else if (LT == 'f' || LT == 'e' || LT == 'g' || LT == 'a')
		parsedbl(flags, args);
	else if (LT == 'c')
		parsechar(flags, args);
	else if (LT == 's')
		parsestr(flags, args);
	else if (LT == 'u' || LT == 'o' || LT == 'x' || TYPE == 'b')
		parseunum(flags, args);
	else if (LT == 'd' || LT == 'i')
		parsenum(flags, args);
	else
		parsepct(flags);
}
