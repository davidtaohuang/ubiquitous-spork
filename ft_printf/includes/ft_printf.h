/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 22:02:41 by dhuang            #+#    #+#             */
/*   Updated: 2017/01/12 20:01:02 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <wchar.h>
# include "../../libft/includes/libft.h"

/*
**	t_format stores all information for a single format string conversion
**	1. 	All char types are simple yes/no checks for the specified flags.
**	2. 	negp marks if a negative precision is set using *
**	3. 	wast marks if the width was set using *
**	4. 	wl and pl track where in the format string width and precision were
**		set, used for * compatibility
**	5. 	elen and ep are used specifically for eE conversions; basically as
**		extra varilables
**	6. 	arg stores the argument, regardless of type
**	7.	bytelen stores the size of the argument
*/

typedef struct	s_format
{
	char	flagzero;
	char	flagplus;
	char	flagminus;
	char	flagpound;
	char	flagspace;
	char	negp;
	char	wast;
	int		width;
	int		wl;
	int		precision;
	int		pl;
	int		length;
	char	conversion;
	int		elen;
	int		ep;
	void	*arg;
	int		bytelen;
}				t_format;

/*
**	t_data stores meta-information
**	1.	str is the formatted output string
**	2.	old is the remaining format string
**	3. 	bytelen is the length of the output string in bytes, to be returned
**		on completion
*/

typedef struct	s_data
{
	char	*str;
	char	*old;
	int		bytelen;
}				t_data;

/*
**	Macros that help my functions pass norm (mainly column width limits),
**	trying to be consistent with their usage.
**	1.	pf is the name of my t_data struct and flags is the name of my
**		t_format struct.
**	2.	I don't use macros the macros until parseswitch; I think it will
**		help make it more legible, at least initially. Added some comments
**		to clarify specific ones in padding functions
**	3.	SA is an odd one, it's meant for checking null or zero values
**		after argument is converted to a string
*/

# define STR pf->str
# define BLEN pf->bytelen
# define TYPE flags->conversion
# define LT ft_tolower(flags->conversion)
# define LEN flags->length
# define ARG flags->arg
# define FBLEN flags->bytelen
# define FGP flags->flagplus
# define FGS flags->flagspace
# define FGN flags->flagpound
# define FGM flags->flagminus
# define FGZ flags->flagzero
# define P flags->precision
# define EP flags->ep
# define ELEN flags->elen
# define W flags->width
# define SA ((char*)flags->arg)[0]

/*
**	General flow of ft_printf can be seen here:
**	1. 	ft_printf is called, find_format identifies first format string
**		segment that needs to be converted
**	2.	datasetup and datasetup2 allocate memory for t_format and parse
**		data from format string segment (findast, find and findlength are
**		included here)
**	3.	parseswitch starts the conversion process which is generally converting
**		the argument into a string, and then formatting/padding it. Generally,
**		conversions happen in my "format*" functions and formmatting/padding
**		happens in my "pad*" functions
**	4.	insertformat includes ft_strndup, ft_pfstrnj (custom string join
**		function for ft_printf), and cutformat; builds the output string
**	5.	parse* block
**	6.	format* block
**	7.	pad* block; the file padswitch is left over from previous structure, it
**		contains the switch functions and pad functions for invalid/%
**		conversions
**	8.	functions specifically used in floating point conversions (just eEfF)
**	9.	stitch helper functions for formatting/padding
*/

int				ft_printf(const char *restrict format, ...);
int				ft_asprintf(char **ret, const char *restrict format, ...);
void			datasetup(t_format *flags, char *format, va_list *args);
void			findast(t_format *flags, char *tmp, int len, va_list *args);
void			findlength(t_format *flags, char *tmp, int len);
void			parseswitch(t_format *flags, va_list *args, t_data *pf);
void			insertformat(t_data *pf, int len);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_pfstrnj(char *s1, size_t len1, char *s2, size_t len2);
void			cutformat(t_data *pf, t_format *flags);

void			parsezjt(t_format *flags, va_list *args, t_data *pf);
void			parsedbl(t_format *flags, va_list *args);
void			parsenum(t_format *flags, va_list *args);
void			parsechar(t_format *flags, va_list *args);
void			parsestr(t_format *flags, va_list *args);
void			parseunum(t_format *flags, va_list *args);

void			formatdbl(t_format *flags);
void			formatedbl(t_format *flags);
void			formatnum(t_format *flags);
void			formatunum(t_format *flags);
void			formatzjt(t_format *flags);

void			padcs(t_format *flags);
void			padnum(t_format *flags);
void			padhex(t_format *flags);
void			padoct(t_format *flags);
void			padgen(t_format *flags);

char			ft_dtoa(double n, int p, char *frac);
char			ft_etoa(double n, char *frac, t_format *flags);
char			*adddigit(char *dec);
int				rounding(char *dec, int i);
char			*makeinfnan(double n);
char			*adddecpt(char *dec, int len);

void			*stitch2(char *s1, char *s2);
void			*stitch3(char *s1, char *s2, char *s3);

#endif
