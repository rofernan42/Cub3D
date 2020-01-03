/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skyfloor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:08:14 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/03 11:06:41 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_color(t_cub3d *cub, int x, int param)
{
	int y;
	int end;

	if (param == 1)
	{
		y = cub->draw_end;
		end = cub->res_y;
	}
	else if (param == 2)
	{
		y = 0;
		end = cub->draw_start;
	}
	while (y < end)
	{
		ft_memmove(&cub->img_ptr[(cub->res_x * y + x) * cub->bit_pix / 8], \
				&cub->tex[4].color, sizeof(int));
		y++;
	}
}

void	draw_floor(t_cub3d *cub, int x)
{
	int y;

	double floorxwall, floorywall;
	double distplayer, currentdist;
	double weight;
	double currentfloorx, currentfloory;
	int floortexx, floortexy, coor_tex;

	if (cub->tex[4].texture == 1)
	{
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
		else if (cub->side == 3)
		{
			floorxwall = cub->map_x + cub->wall_x;
			floorywall = cub->map_y;
		}
		else if (cub->side == 4)
		{
			floorxwall = cub->map_x + cub->wall_x;
			floorywall = cub->map_y + 1.0;
		}
		// printf("%f\n", cub->wall_x);
		// printf("%f   %f\n", floorxwall, floorywall);
		if (cub->draw_end < 0)
			cub->draw_end = cub->res_y;
		y = cub->draw_end;
		while (y < cub->res_y)
		{
			currentdist = cub->res_y / (2.0 * (double)y - cub->res_y);
			weight = currentdist / cub->wall_dist;
			currentfloorx = weight * floorxwall + (1.0 - weight) * cub->pos_x;
			currentfloory = weight * floorywall + (1.0 - weight) * cub->pos_y;
			floortexx = (int)(currentfloorx * cub->tex[4].width) % cub->tex[4].width;
			floortexy = (int)(currentfloory * cub->tex[4].height) % cub->tex[4].height;
			coor_tex = floortexx * cub->tex[4].bit_pix / 8
						+ floortexy * cub->tex[4].size_line;
			// printf("%f   %f\n", currentfloorx, currentfloory);
			// printf("%d %d %d %d\n", cub->tex[4].width, cub->tex[4].height, cub->tex[4].bit_pix, cub->tex[4].size_line);
						// printf("%f   %f   %f\n", currentdist, weight, cub->wall_dist);
			ft_memmove(&cub->img_ptr[(cub->res_x * y + x) * cub->tex[4].bit_pix / 8], &cub->tex[4].img_ptr[coor_tex], sizeof(int));
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
