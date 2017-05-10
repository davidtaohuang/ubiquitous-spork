/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:34:51 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/28 16:34:51 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include "../libft/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"
# include "mlx.h"

typedef union	u_col
{
	unsigned int	c;
	unsigned char	rgb[4];
}				t_col;

typedef struct	s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct	s_tex
{
	int				h;
	int				w;
	int				line;
	int				bbp;
	int				endian;
	void			*img;
	unsigned int	*imgd;
}				t_tex;

typedef struct	s_mlxdata
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*imgd;
	int				bbp;
	int				endian;
	int				line;
	char			**wmap;
	t_tex			*wtex;
	t_tex			*ctex;
	t_tex			*ftex;
	t_vec			mapsize;
	t_vec			pos;
	t_vec			odir;
	t_vec			dir;
	t_vec			plane;
	t_vec			oplane;
	t_vec			raypos;
	t_vec			raydir;
	t_vec			map;
	t_vec			side;
	t_vec			delta;
	int				angle;
	double			wall;
	double			wallx;
	double			camx;
	char			shift;
	char			updown;
	char			leftright;
}				t_mlxdata;

typedef struct	s_meta
{
	// char			type;
	// char			lock;
	// char			info;
	// int				mbutton;
	// int				mdown;
	// char			**wmap;
	t_mlxdata		*d;
	// void			(*frac)(t_mlxdata*, int);
}				t_meta;

/*
**	t_thread is a basic struct for multi-threading
**
**	1.	tid is the thread id
**	2.	d is the mlx data that frac needs to do calculations
**	3.	frac is the pointer to corresponding fractal calculating function
*/

typedef struct	s_thread
{
	int				tid;
	t_mlxdata		*d;
	// void			(*frac)(t_mlxdata*, int);
}				t_thread;

/*
**	The following macros can be modified to change the viewing experience.
**
**	1.	THREAD_COUNT - the number of threads created for multi-threading
**	2.	CSMOOTH - toggles whether the color-smoothing option is used (can
**		be 0 or 1)
**	3.	MITER - specifies maximum iterations used in fractal calculations
**	4.	WIN2X - horizontal size of the image/window in pixels
**	5.	WIN2Y - vertical size of the image/window in pixels
**	6.	NTOL - tolerance used in the boundary condition in calculating the
**		newton fractol
**	7.	CR - color range
**	8.	CO - color offset
**	9.	XO - specifies intial value for x-range, used in conjunction with
**		XR to specify initial domain (in terms of the complex plane)
**	10.	XR - specifies initial domain in the complex plane displayed in the
**		image/window
**	11.	YO - specifies intial value for y-range, used in conjunction with
**		YR to specify initial range (in terms of the complex plane)
**	12.	YR - specifies initial range in the complex plane displayed in the
**		image/window
**	13.	ZOOM - constant for zoom calculations
**	14.	ENDIAN - hardware specific
**	15. BBP - bits per pixel (you can change this, but mlx might break)
**
**	XO, XR, YO, YR example:
**
**	XO = -2, XR = 4 for example specifies that the initial domain starts at
**	-2 and has a range of 4, meaning that the domain is (-2, -2 + 4) =
**	(-2, 2)
**
**	YO and YR function roughly the same way
*/

# define WINX 512
# define WINY 384
# define D2RAD(x) (x * M_PI / 180)
# define RA (double)D2RAD(d->angle)
# define THREAD_COUNT 16
# define CR 0x0000FFFF
# define CO 0x00FF0000
# define ENDIAN 0
# define BBP 32

# define TH 64
# define TW 64
# define mapWidth 24
# define mapHeight 24
# define PI M_PI
# define MSPD 0.1
# define RSPD 1.5

/*
**	These macros are all derived and thus really shouldn't be modified.
**
**	1.	WINX - used to simplify calculations
**	2.	WINY - used to simplify calculations
**	3.	CHUNK - specifies how many pixels are calulated and assigend by
**		each thread
**	4.	CI - simple color assignment
**	5.	CS - color smoothing calculation
**	6.	XOFFSET - used to help keep functions within line and column limits
**	7.	YOFFSET - used to help keep functions within line and column limits
**	8.	LINE - calculates width of an image in terms of bytes, used to
**		create imgd
*/

# define LINE WINX * BBP / 8

/*
**	Hook functions
*/

int				ft_kup(int key, t_mlxdata *d);
int				ft_kdown(int key, t_mlxdata *d);
int       		exit_hook(int key, t_mlxdata *d);
void			raycaster(t_mlxdata *d);
void			drawfc(t_mlxdata *d, int side, int drawend, int i);
void			shade(t_col *c, int a, int b);

void			maketex(t_mlxdata *d, char *str, t_tex **tex);
void			maketextures(t_mlxdata *d);

int				ft_redraw(t_mlxdata *d);

t_mlxdata		*ft_getmap(char *file);

t_mlxdata		*mlxsetup(t_vec size, t_vec start);

void			ft_puterror(int code);

void			ft_freetmp(char **tmp);
void			ft_freemlxdata(t_mlxdata *d);
void			ft_linecleanup(char **tmp);
void			ft_cleanall(t_mlxdata *d, char **tmp);
// int				ft_mmove(int x, int y, t_fmeta *meta);
// int				ft_mdown(int button, int x, int y, t_fmeta *meta);
// int				ft_mup(int button, int x, int y, t_fmeta *meta);

/*
**	Drawing/MLX functions
*/

// void			mlxdraw(t_mlxdata *d);

#endif
