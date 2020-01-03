/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skyfloor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:08:14 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/03 17:40:07 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_color(t_cub3d *cub, int x, int param)
{
	int y;
	int end;
	int ind;

	if (param == 1)
	{
		y = cub->draw_end;
		end = cub->res_y;
		ind = 4;
	}
	else if (param == 2)
	{
		y = 0;
		end = cub->draw_start;
		ind = 5;
	}
	while (y < end)
	{
		ft_memmove(&cub->img_ptr[(cub->res_x * y + x) * cub->bit_pix / 8], \
				&cub->tex[ind].color, sizeof(int));
		y++;
	}
}



void	draw_floor(t_cub3d *cub, int x)
{
	int y;

	if (cub->tex[4].texture == 1)
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
		// printf("%f\n", cub->wall_x);
		// printf("%f   %f\n", cub->flr.fl_x_wall, cub->flr.fl_y_wall);
		if (cub->draw_end < 0)
			cub->draw_end = cub->res_y;
		y = cub->draw_end;
		while (y < cub->res_y)
		{
			cub->flr.cur_dist = fabs(cub->res_y / (2.0 * y - cub->res_y));
			cub->flr.weight = cub->flr.cur_dist / cub->wall_dist;
			cub->flr.cur_fl_x = cub->flr.weight * cub->flr.fl_x_wall + (1.0 - cub->flr.weight) * cub->pos_x;
			cub->flr.cur_fl_y = cub->flr.weight * cub->flr.fl_y_wall + (1.0 - cub->flr.weight) * cub->pos_y;
			cub->flr.fl_tex_x = (int)(cub->flr.cur_fl_x * cub->tex[4].width) % cub->tex[4].width;
			cub->flr.fl_tex_y = (int)(cub->flr.cur_fl_y * cub->tex[4].height) % cub->tex[4].height;
			cub->flr.fl_tex = cub->flr.fl_tex_x * cub->tex[4].bit_pix / 8
						+ cub->flr.fl_tex_y * cub->tex[4].size_line;
			// printf("%f\n", cub->flr.cur_dist);
			// printf("%f   %f\n", cub->flr.cur_fl_x, cub->flr.cur_fl_y);
			// printf("%d   %d\n", cub->flr.fl_tex_x, cub->flr.fl_tex_y);
			// printf("%d %d %d %d\n", cub->tex[4].width, cub->tex[4].height, cub->tex[4].bit_pix, cub->tex[4].size_line);
						// printf("%f   %f   %f\n", cub->flr.cur_dist, cub->flr.weight, cub->wall_dist);
			ft_memmove(&cub->img_ptr[(cub->res_x * y + x) * cub->tex[4].bit_pix / 8], &cub->tex[4].img_ptr[cub->flr.fl_tex], sizeof(int));
			y++;
		}
	}
		else
			draw_color(cub, x, 1);
}

void	draw_ceiling(t_cub3d *cub, int x)
{
	int y;
	int skytex;

	y = 0;
	if (cub->tex[5].texture == 1)
	{
		while (y < cub->draw_start)
		{
			skytex = x % cub->tex[5].width * cub->tex[5].bit_pix / 8
					+ y % cub->tex[5].height * cub->tex[5].size_line;
			ft_memmove(&cub->img_ptr[(cub->res_x * y + x) * cub->tex[5].bit_pix / 8], &cub->tex[5].img_ptr[skytex], sizeof(int));
			y++;
		}
	}
	else
		draw_color(cub, x, 2);
	
}
