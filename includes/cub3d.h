/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:08:32 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 18:31:16 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "Libft/libft.h"

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13

# define KEY_H 4

# define KEY_TAB 48
# define KEY_SPACE 49
# define KEY_ESC 53
# define KEY_SHIFT 257

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

typedef struct		s_buf
{
	char			*content;
	char			**buffer;
}					t_buf;

typedef struct		s_tex
{
	int				texture;
	int				col;
	int				color;
	int				width;
	int				height;
	char			*tex_path;
	void			*image;
	void			*tex_ptr;
	int				bit_pix;
	int				size_line;
	int				endian;
	int				pix;
}					t_tex;

typedef struct		s_floor
{
	double			fl_x_wall;
	double			fl_y_wall;
	double			cur_dist;
	double			weight;
	double			cur_fl_x;
	double			cur_fl_y;
	int				fl_tex_x;
	int				fl_tex_y;
}					t_floor;

typedef struct		s_coor
{
	double			x;
	double			y;
}					t_coor;

typedef struct		s_sprite
{
	double			*distbuf;
	int				nb_sprite;
	int				*sp_order;
	double			*sp_dist;
	double			sp_x;
	double			sp_y;
	double			inv_det;
	double			trans_x;
	double			trans_y;
	int				sp_screen;
	int				sp_h;
	int				sp_w;
	int				draw_startx;
	int				draw_endx;
	int				draw_starty;
	int				draw_endy;
	int				tsp_x;
	int				tsp_y;
}					t_sprite;

typedef struct		s_action
{
	int				up;
	int				down;
	int				r_left;
	int				m_left;
	int				r_right;
	int				m_right;
	double			m_speed;
	double			r_speed;
	int				hud;
}					t_action;

typedef struct		s_cub3d
{
	t_buf			buf;
	int				screenshot;
	char			**map;
	int				map_h;
	int				map_w;
	void			*mlx_ptr;
	void			*win_ptr;
	int				res_x;
	int				res_y;
	void			*image;
	void			*img_ptr;
	int				bit_pix;
	int				size_line;
	int				endian;
	int				map_x;
	int				map_y;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			cam_plane;
	double			raydir_x;
	double			raydir_y;
	double			side_dx;
	double			side_dy;
	double			delta_dx;
	double			delta_dy;
	double			wall_dist;
	int				step_x;
	int				step_y;
	int				wall_hit;
	int				side;
	int				line_h;
	int				draw_start;
	int				draw_end;
	double			olddir_x;
	double			oldplane_x;
	t_action		act;
	t_tex			tex[7];
	double			wall_x;
	int				x_coor;
	int				y_coor;
	t_floor			flr;
	t_coor			*c_spr;
	t_sprite		spr;
}					t_cub3d;

typedef struct		s_bmp
{
	int				filesize;
	char			*img;
	unsigned char	fileheader[14];
	unsigned char	infoheader[40];
	unsigned char	pad[3];
	int				color;
	int				fd;
}					t_bmp;

/*
** INIT_DESC.C
*/
void				init_desc(t_cub3d *cub, char *desc);

/*
** CHECK_CONTENT.C
*/
void				check_content(t_cub3d *cub);

/*
** BMP.C
*/
void				convert_bmp(t_cub3d *cub);

/*
** RESOLUTION.C
*/
void				assign_res(t_cub3d *cub);

/*
** CREATE_MAP.C
*/
void				create_map(t_cub3d *cub);

/*
** ARRANGE_MAP.C
*/
void				adjust_map(t_cub3d *cub);
void				complete_map(t_cub3d *cub);

/*
** CHECK_MAP.C
*/
void				check_map(t_cub3d *cub);

/*
** TEXTURES.C
*/
void				get_textures(t_cub3d *cub);

/*
** INIT_VAR.C
*/
void				init_var(t_cub3d *cub);

/*
** ACTIONS.C
*/
int					key_press(int key, t_cub3d *cub);
int					key_release(int key, t_cub3d *cub);

/*
** PIX.C
*/
void				get_color(t_cub3d *cub, int ind, int x, int y);
void				color_dist(t_cub3d *cub, int ind, double dist);
void				draw_pix(t_cub3d *cub, int ind, int x, int y);

/*
** DRAW_*.C
*/
void				draw_walls(t_cub3d *cub, int x);
void				draw_floor(t_cub3d *cub, int x);
void				draw_ceiling(t_cub3d *cub, int x);
void				draw_sky(t_cub3d *cub, int x);
void				draw_all(t_cub3d *cub, int x);

/*
** SPRITE_SORTING.C
*/
void				count_sprites(t_cub3d *cub);
void				create_sorting(t_cub3d *cub);
void				sort_sprites(int *order, double *dist, int amount);

/*
** SPRITE.C
*/
void				sprites(t_cub3d *cub);

/*
** RAYCASTING.C
*/
void				raycasting(t_cub3d *cub);

/*
** IMAGE.C
*/
void				put_image(t_cub3d *cub);

/*
** HUD.C
*/
void				hud(t_cub3d *cub);

/*
** MOTION.C
*/
int					motion(t_cub3d *cub);

/*
** ERROR.C
*/
void				display_error(t_cub3d *cub, char *err_message);

/*
** FREE.C
*/
void				free_all(t_cub3d *cub);

/*
** EXIT.C
*/
int					exit_prog(t_cub3d *cub);

/*
** MAIN.C
*/
int					main(int argc, char **argv);

#endif
