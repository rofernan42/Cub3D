/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:08:14 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/10 17:17:50 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	def_floor_side(t_cub3d *cub)
{
	if (cub->side == 0)
	{
		cub->flr.fl_x_wall = cub->map_x;
		cub->flr.fl_y_wall = cub->map_y + cub->wall_x;
	}
	else if (cub->side == 1)
	{
		cub->flr.fl_x_wall = cub->map_x + 1.0;
		cub->flr.fl_y_wall = cub->map_y + cub->wall_x;
	}
	else if (cub->side == 2)
	{
		cub->flr.fl_x_wall = cub->map_x + cub->wall_x;
		cub->flr.fl_y_wall = cub->map_y;
	}
	else if (cub->side == 3)
	{
		cub->flr.fl_x_wall = cub->map_x + cub->wall_x;
		cub->flr.fl_y_wall = cub->map_y + 1.0;
	}
}

static void	set_tex_coor(t_cub3d *cub, int ind)
{
	cub->flr.weight = cub->flr.cur_dist / cub->wall_dist;
	cub->flr.cur_fl_x = cub->flr.weight * cub->flr.fl_x_wall \
						+ (1.0 - cub->flr.weight) * cub->pos_x;
	cub->flr.cur_fl_y = cub->flr.weight * cub->flr.fl_y_wall \
						+ (1.0 - cub->flr.weight) * cub->pos_y;
	cub->flr.fl_tex_x = (int)(cub->flr.cur_fl_x * cub->tex[ind].width) \
						% cub->tex[ind].width;
	cub->flr.fl_tex_y = (int)(cub->flr.cur_fl_y * cub->tex[ind].height) \
						% cub->tex[ind].height;
}

void		draw_floor(t_cub3d *cub, int x)
{
	int y;

	def_floor_side(cub);
	if (cub->draw_end < 0)
		cub->draw_end = cub->res_y;
	y = cub->draw_end;
	while (y < cub->res_y)
	{
		cub->flr.cur_dist = cub->res_y / (2.0 * y - cub->res_y);
		if (cub->tex[4].texture == 1)
		{
			set_tex_coor(cub, 4);
			get_color(cub, 4, cub->flr.fl_tex_x, cub->flr.fl_tex_y);
		}
		else
			cub->tex[4].color = cub->tex[4].col;
		color_dist(cub, 4, cub->flr.cur_dist);
		draw_pix(cub, 4, x, y);
		y++;
	}
}

void		draw_ceiling(t_cub3d *cub, int x)
{
	int y;

	y = 0;
	while (y < cub->draw_start)
	{
		cub->flr.cur_dist = -cub->res_y / (2.0 * y - cub->res_y);
		if (cub->tex[5].texture == 1)
		{
			set_tex_coor(cub, 5);
			get_color(cub, 5, cub->flr.fl_tex_x, cub->flr.fl_tex_y);
		}
		else
			cub->tex[5].color = cub->tex[5].col;
		color_dist(cub, 5, cub->flr.cur_dist);
		draw_pix(cub, 5, x, y);
		y++;
	}
}

void		draw_sky(t_cub3d *cub, int x)
{
	int y;
	int skytex;

	y = 0;
	while (y < cub->draw_start)
	{
		skytex = \
		(int)(x - cub->tex[5].width * (M_PI / 2) \
		* atan(cub->dir_y / cub->dir_x)) \
		* cub->tex[5].bit_pix / 8 \
		+ y * cub->tex[5].size_line;
		ft_memmove((cub->img_ptr + (cub->res_x * y + x) * \
					cub->tex[5].bit_pix / 8), \
					(cub->tex[5].tex_ptr + skytex), sizeof(int));
		y++;
	}
}
