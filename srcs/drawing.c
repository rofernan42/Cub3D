/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:08:14 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/17 17:26:08 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		define_tex_wall(t_cub3d *cub)
{
	int ind;

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

void	draw_walls(t_cub3d *cub, int x)
{
	int y;
	int ind;
	int coor_tex;

	ind = define_tex_wall(cub);
	y = cub->draw_start;
	if (cub->side == 0 || cub->side == 1)
		cub->wall_x = cub->pos_y + cub->wall_dist * cub->raydir_y;
	else if (cub->side == 2 || cub->side == 3)
		cub->wall_x = cub->pos_x + cub->wall_dist * cub->raydir_x;
	if (cub->tex[ind].texture == 1)
	{
		cub->x_coor = (int)(cub->wall_x * (double)(cub->tex[ind].width));
		if ((cub->side == 0 || cub->side == 1) && cub->raydir_x > 0)
			cub->x_coor = cub->tex[ind].width - cub->x_coor - 1;
		if ((cub->side == 2 || cub->side == 3) && cub->raydir_y < 0)
			cub->x_coor = cub->tex[ind].width - cub->x_coor - 1;
		cub->x_coor = abs(cub->x_coor);
		while (y < cub->draw_end)
		{
			cub->y_coor = y * 256 - cub->res_y * 128 + cub->line_h * 128;
			cub->y_coor = cub->y_coor * cub->tex[ind].height / cub->line_h / 256;
			coor_tex = cub->x_coor % cub->tex[ind].width * cub->tex[ind].bit_pix / 8
					+ cub->y_coor % cub->tex[ind].height * cub->tex[ind].size_line;
			ft_memmove(cub->img_ptr + (cub->res_x * y + x) * cub->bit_pix / 8, \
					&cub->tex[ind].img_ptr[coor_tex], sizeof(int));
			y++;
		}
	}
	else
	{
		while (y < cub->draw_end)
		{
			ft_memmove(cub->img_ptr + 4 * cub->res_x * y + x * 4, \
					&cub->tex[ind].color, sizeof(int));
			y++;
		}
	}
}

void	draw_floor(t_cub3d *cub, int x)
{
	int y;

	double floorxwall, floorywall;
	double distwall, distplayer, currentdist;
	double weight;
	double currentfloorx, currentfloory;
	int floortexx, floortexy;

	if (cub->side == 0)
	{
		floorxwall = cub->map_x;
		floorywall = cub->map_y + cub->wall_x;
	}
	else if (cub->side == 1)
	{
		floorxwall = cub->map_x + 1.0;
		floorywall = cub->map_y + cub->wall_x;
	}
	else if (cub->side == 2)
	{
		floorxwall = cub->map_x + cub->wall_x;
		floorywall = cub->map_y;
	}
	else if (cub->side == 3)
	{
		floorxwall = cub->map_x + cub->wall_x;
		floorywall = cub->map_y + 1.0;
	}
	distwall = cub->wall_dist;
	if (cub->draw_end < 0)
		cub->draw_end = cub->res_y;
	y = cub->draw_end + 1;
	while (y < cub->res_y)
	{
		currentdist = cub->res_y / (2.0 * y - cub->res_y);
		weight = currentdist / distwall;
		currentfloorx = weight * floorxwall + (1.0 - weight) * cub->pos_x;
		currentfloory = weight * floorxwall + (1.0 - weight) * cub->pos_y;
		floortexx = (int)(currentfloorx * cub->tex[4].width) % cub->tex[4].width;
		floortexy = (int)(currentfloory * cub->tex[4].height) % cub->tex[4].height;
		int coor_tex = floortexx * cub->tex[4].bit_pix / 8
					+ floortexy * cub->tex[4].size_line;
		ft_memmove(cub->img_ptr + (cub->res_x * y + x) * cub->bit_pix / 8, \
					&cub->tex[4].img_ptr[coor_tex], sizeof(int));
		y++;
	}
	// y = cub->draw_end;
	// while (y < cub->res_y)
	// {
	// 	ft_memmove(cub->img_ptr + 4 * cub->res_x * y + x * 4, \
	// 				&cub->tex[4].color, sizeof(int));
	// 	y++;
	// }
}

void	draw_ceiling(t_cub3d *cub, int x)
{
	int y;

	y = 0;
	while (y < cub->draw_start)
	{
		ft_memmove(cub->img_ptr + 4 * cub->res_x * y + x * 4, \
					&cub->tex[5].color, sizeof(int));
		y++;
	}
}
