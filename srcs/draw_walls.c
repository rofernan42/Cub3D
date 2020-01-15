/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 10:49:00 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 14:35:29 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	define_tex_wall(t_cub3d *cub)
{
	int ind;

	ind = 0;
	if (cub->side == 0)
		ind = 0;
	else if (cub->side == 1)
		ind = 1;
	else if (cub->side == 2)
		ind = 2;
	else if (cub->side == 3)
		ind = 3;
	return (ind);
}

static void	draw_color(t_cub3d *cub, int x, int ind)
{
	int y;

	y = cub->draw_start;
	while (y < cub->draw_end)
	{
		cub->tex[ind].color = cub->tex[ind].col;
		color_dist(cub, ind, cub->wall_dist);
		draw_pix(cub, ind, x, y);
		y++;
	}
}

static void	set_tex_coor(t_cub3d *cub, int x, int ind)
{
	int y;

	cub->x_coor = (int)(cub->wall_x * (double)(cub->tex[ind].width));
	if ((cub->side == 0 || cub->side == 1) && cub->raydir_x > 0)
		cub->x_coor = cub->tex[ind].width - cub->x_coor - 1;
	if ((cub->side == 2 || cub->side == 3) && cub->raydir_y < 0)
		cub->x_coor = cub->tex[ind].width - cub->x_coor - 1;
	cub->x_coor = abs(cub->x_coor);
	y = cub->draw_start;
	while (y < cub->draw_end)
	{
		cub->y_coor = y * 256 - cub->res_y * 128 + cub->line_h * 128;
		cub->y_coor = cub->y_coor * cub->tex[ind].height / cub->line_h / 256;
		get_color(cub, ind, cub->x_coor, cub->y_coor);
		color_dist(cub, ind, cub->wall_dist);
		draw_pix(cub, ind, x, y);
		y++;
	}
}

void		draw_walls(t_cub3d *cub, int x)
{
	int ind;

	ind = define_tex_wall(cub);
	if (cub->side == 0 || cub->side == 1)
		cub->wall_x = cub->pos_y + cub->wall_dist * cub->raydir_y;
	else if (cub->side == 2 || cub->side == 3)
		cub->wall_x = cub->pos_x + cub->wall_dist * cub->raydir_x;
	cub->wall_x = cub->wall_x - floor(cub->wall_x);
	if (cub->tex[ind].texture == 1)
		set_tex_coor(cub, x, ind);
	else
		draw_color(cub, x, ind);
}
