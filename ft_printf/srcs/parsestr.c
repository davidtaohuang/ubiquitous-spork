/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsestr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 21:15:33 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/25 21:15:33 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	parsewc(t_format *flags, va_list *args)
{
	wchar_t	*tmp;

	tmp = (wchar_t*)ft_memalloc(sizeof(wchar_t) * 2);
	*tmp = va_arg(*args, wchar_t);
	flags->arg = ft_wstouni(tmp);
	if (*tmp)
		FBLEN = ft_strlen(flags->arg);
	else
		FBLEN = 1;
	ft_memdel((void**)&tmp);
}

static void	parsews(t_format *flags, va_list *args)
{
	wchar_t	*tmp;

	tmp = va_arg(*args, wchar_t*);
	if (tmp)
	{
		flags->arg = ft_wstouni(tmp);
		FBLEN = ft_strlen(flags->arg);
	}
	else
	{
		flags->arg = ft_strdup("(null)");
		FBLEN = 6;
		LEN = 0;
	}
	if (flags->negp && P < FBLEN)
		P = FBLEN;
}

void		parsechar(t_format *flags, va_list *args)
{
	if (TYPE == 'C')
		LEN = 1;
	if (LEN == 1)
		parsewc(flags, args);
	else
	{
		flags->arg = (char*)ft_memalloc(sizeof(char) * 2);
		*(char*)(flags->arg) = va_arg(*args, int);
		FBLEN = 1;
	}
	padcs(flags);
}

void		parsestr(t_format *flags, va_list *args)
{
	char	*tmp;

	if (TYPE == 'S')
		LEN = 1;
	if (LEN == 1)
		parsews(flags, args);
	else
	{
		tmp = va_arg(*args, char*);
		if (tmp)
		{
			flags->arg = ft_strdup(tmp);
			FBLEN = ft_strlen((char*)(flags->arg));
		}
		else
		{
			flags->arg = ft_strdup("(null)");
			FBLEN = 6;
		}
		if (flags->negp && P < FBLEN)
			P = FBLEN;
	}
	padcs(flags);
}
