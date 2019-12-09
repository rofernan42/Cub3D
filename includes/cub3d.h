/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:08:32 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/09 16:09:15 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Libft/libft.h"

/*
** http://projet-moteur-3d.e-monsite.com/pages/raycasting/raycasting.html
** https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html
** https://user.oc-static.com/ftp/mateo21/sdlkeysym.html
**
** IMPORTANT: Event et EventMask: https://code.woboq.org/qt5/include/X11/X.h.html

** tuto raycasting: https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
** code C tuto: http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=s3De
** https://lodev.org/cgtutor/raycasting.html
*/

/* Fonctions externes autorisées:
** -open, read, write, malloc, free, perror,
** strerror, exit
** -Toutes les fonctions de la lib math (-lm
** man man 3 math)
** -Toutes les fonctions de la MinilibX
http://www-igm.univ-mlv.fr/~berstel/Cours/Xlib/13-Evenements.pdf
*/

typedef struct	s_map
{
	int			height;
	char		*err_message;
}				t_map;

typedef struct	s_tex
{
	char		*tex_n;
	char		*tex_s;
	char		*tex_e;
	char		*tex_w;
	void		*image;
	void		*img_ptr;
	int			bit_pix;
	int			size_line;
	int			endian;
}				t_tex;

typedef struct	s_cub3d
{
	char		**map;
	int			map_h;
	int			map_w;
	void		*mlx_ptr;
	void		*win_ptr;
	int			res_x;
	int			res_y;
	void		*image;
	void		*img_ptr;
	int			bit_pix;
	int			size_line;
	int			endian;
	int			map_x;
	int			map_y;
	double		pos_x;
	double		pos_y;		//x and y start position
	double		dir_x;
	double		dir_y;		//initial direction vector
	double		plane_x;
	double		plane_y;	//the 2d raycaster version of camera plane
	double		cam_plane;	//x-coordinate in camera space
    double		raydir_x;
    double		raydir_y;
	double		side_dx;	//length of ray from current position to next x or y-side
    double		side_dy;
    double		delta_dx;	//length of ray from one x or y-side to next x or y-side
	double		delta_dy;
    double		wall_dist;
    int			step_x;		//what direction to step in x or y-direction (either +1 or -1)
    int			step_y;
	int			wall_hit;	//was there a wall hit?
	int			side;		//was a NS or a EW wall hit?
	int			line_height;
	int			draw_start;
    int			draw_end;
	double		mov_speed;
	double		rot_speed;
	double		olddir_x;
	double		oldplane_x;
	int			up;
	int			down;
	int			left;
	int			right;
	t_tex		tex;
	int			error;
	char		*err_message;
}				t_cub3d;

/*
** CREATE_MAP.C
*/
void			count_x(int fd, t_cub3d *cub);
void			create_map(int fd, t_cub3d *cub);
void			adjust_map(t_cub3d *cub);
void			complete_map(t_cub3d *cub);

/*
** CHECK_MAP.C
*/
void			check_map(t_cub3d *cub);

/*
** TEXTURES.C
*/
void			init_textures(t_cub3d *cub);
void			assign_tex(t_cub3d *cub, char *line);
void			import_tex(t_cub3d *cub);

/*
** INIT_VAR.C
*/
void			init_cub(t_cub3d *cub);
void			init_position(t_cub3d *cub);
void			init_direction(t_cub3d *cub);
void			init_plane(t_cub3d *cub);
void			init_var(t_cub3d *cub);

/*
** DRAWING.C
*/
void			draw_walls(t_cub3d *cub, int x);
void			draw_floor(t_cub3d *cub, int x);
void			draw_ceiling(t_cub3d *cub, int x);

/*
** RAYCASTING.C
*/
void			raycasting(t_cub3d *cub);

/*
** ACTIONS.C
*/
int				press_key(int key, t_cub3d *cub);
int				real_key(int key, t_cub3d *cub);

/*
** MOTION.C
*/
int				motion(t_cub3d *cub);

/*typedef struct	s_tex
{
	int			;
	int			res_y;
}				t_tex;
*/
#endif
