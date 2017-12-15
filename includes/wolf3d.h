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
**	2.	WINX - horizontal size of the graphics window in pixels
**	3.	WINY - vertical size of the graphics window in pixels
**	4.	MAPXMAX - maximum horizontal size of the map file
**	5.	MAPYMAX - maximum vertical size of the map file
**	6.	MSPD - default movement speed in map units
**	7.	WSPD - walking speed in map units
**	8.	SSPD - sprinting speed in map units
**	9.	RSPD - default rotation speed in degrees
**
**	Modifications to MSPD, WSPD, and SSPD can cause aberrant behavior.
**	Be careful.
*/

# define THREAD_COUNT 16
# define WINX 800
# define WINY 600
# define MAPXMAX 256
# define MAPYMAX 256
# define MSPD 0.1
# define WSPD 0.05
# define SSPD 0.2
# define RSPD 2

/*
**	CBUF and CBUF2 define values used in the collision calculations. CBUF
**	is used for making sure the player remains inside the boundaries of
**	the map while CBUF2 is determines how close a player can get to a wall.
**
**	These values should not be modified, otherwise collision detection may
**	fail and cause program crashes.
*/

# define CBUF 1.1
# define CBUF2 0.05

/*
**	These macros are derived/integral to the function of program be
**	and should not be modified under any circumstances.
**
**	1.	CHUNK - specifies how many pixels are calulated and assigned by
**		each thread
**	2.	D2RAD - inline function to convert a angle in degrees to radians
**	3.	RA - the angle of rotation from the original direction in radians
**	4.	PI - a macro of the pi approximation macro from math.h
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

int				getaline(const int fd, char **line);
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
