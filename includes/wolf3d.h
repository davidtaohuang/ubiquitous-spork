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

/*
**	t_col defines a union that represents a 32-bit color value. This can be
**	used an unsigned integer or as an unsigned char array of RGB components.
*/

typedef union	u_col
{
	unsigned int	c;
	unsigned char	rgb[4];
}				t_col;

/*
**	t_ivec and t_vec are structs that represent integer and double-precision
**	floating point vectors. This was primarily to organize variables used in
**	the raycasting calculations more easily.
*/

typedef struct	s_ivec
{
	int		x;
	int		y;
}				t_ivec;

typedef struct	s_vec
{
	double	x;
	double	y;
}				t_vec;

/*
**	t_tex is a struct that contains all of the information for each loaded
**	texture.
**
**	1.	h = height in pixels
**	2.	w = width in pixels
**	3.	line = stores the byte (bit?) length of one horizontal line of pixels
**	4.	bbp = bits per pixel
**	5.	img = MLX image pointer
**	6.	imgd = MLX image pixel array
*/

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

/*
**	t_calcs is an intermediary structure containing all of the variables
**	necessary for the raycasting calculations.
*/

typedef struct	s_calcs
{
	double			camx;
	double			wall;
	double			wallx;
	int				wside;
	int				lineheight;
	t_ivec			mapsize;
	t_vec			plane;
	t_vec			raypos;
	t_vec			raydir;
	t_vec			map;
	t_vec			side;
	t_vec			delta;
	t_vec			fwall;
	t_ivec			draw;
	t_ivec			texhit;
	t_col			color;
}				t_calcs;

/*
**	t_mlxdata is the MLX environment and holds all of the information
**	tied to the player, his position, and calculating the field of view.
*/

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
	t_ivec			mapsize;
	t_vec			pos;
	t_vec			odir;
	t_vec			dir;
	t_vec			plane;
	t_vec			oplane;
	int				angle;
	char			info;
	char			shift;
	char			sprint;
	char			walk;
	char			up;
	char			down;
	char			left;
	char			right;
}				t_mlxdata;

/*
**	t_thread is a basic struct for multi-threading
**
**	1.	tid is the thread id
**	2.	d is the mlx data that each needs to do raycasting calculations
*/

typedef struct	s_thread
{
	int				tid;
	t_mlxdata		*d;
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

# define WINX 1600
# define WINY 1200
# define THREAD_COUNT 16
# define MAPXMAX 256
# define MAPYMAX 256
# define MSPD 0.1
# define WSPD 0.05
# define SSPD 0.2
# define RSPD 2
# define CBUF 1.1
# define CBUF2 0.05

/*
**	These macros are derived and thus really shouldn't be modified.
**
**	3.	CHUNK - specifies how many pixels are calulated and assigned by
**		each thread
**	4.	CI - simple color assignment
**	5.	CS - color smoothing calculation
**	6.	XOFFSET - used to help keep functions within line and column limits
**	7.	YOFFSET - used to help keep functions within line and column limits
**	8.	LINE - calculates width of an image in terms of bytes, used to
**		create imgd
*/

# define CHUNK WINX / THREAD_COUNT
# define D2RAD(x) (x * M_PI / 180)
# define RA (double)D2RAD(d->angle)
# define PI M_PI

/*
**	Hook functions
*/

int				ft_kup(int key, t_mlxdata *d);
int				ft_kdown(int key, t_mlxdata *d);
int				exit_hook(int key, t_mlxdata *d);

/*
**	Environment initialization functions (map parsing, etc.)
*/

t_mlxdata		*ft_getmap(char *file);
t_mlxdata		*mlxsetup(t_vec size, t_vec start);

/*
**	Drawing management functions
*/

void			threadmanage(t_mlxdata *d);
int				ft_redraw(t_mlxdata *d);
void			ft_mlxredraw(t_mlxdata *d);

/*
**	Raycasting calculation functions
*/

void			raycaster(t_mlxdata *d, int i);
void			drawfc(t_mlxdata *d, t_calcs *c, int drawend, int i);
void			shade(t_col *c, int a, int b);

/*
**	Cleanup and error functions
*/

void			ft_puterror(int code);
void			ft_freetmp(char **tmp);
void			ft_freemlxdata(t_mlxdata *d);
void			ft_linecleanup(char **tmp);
void			ft_cleanall(t_mlxdata *d, char **tmp);

#endif
