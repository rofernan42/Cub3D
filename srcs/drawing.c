/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:08:14 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/16 17:26:12 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_walls(t_cub3d *cub, int x)
{
	int y;
	int ind;

	if (cub->side == 0)
	{
		if (!cub->tex[0].img_ptr)
			cub->tex[0].color = GREEN;
		ind = 0;
	}
	else if (cub->side == 1)
	{
		if (!cub->tex[1].img_ptr)
			cub->tex[1].color = RED;
		ind = 1;
	}
	else if (cub->side == 2)
	{
		if (!cub->tex[2].img_ptr)
			cub->tex[2].color = BLUE;
		ind = 2;
	}
	else if (cub->side == 3)
	{
		if (!cub->tex[3].img_ptr)
			cub->tex[3].color = YELLOW;
		ind = 3;
	}
	if (cub->side == 0 || cub->side == 1)
		cub->wall_x = cub->pos_y + cub->wall_dist * cub->raydir_y;
	else if (cub->side == 2 || cub->side == 3)
		cub->wall_x = cub->pos_x + cub->wall_dist * cub->raydir_x;
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
		ft_memmove(cub->img_ptr + 4 * cub->res_x * y + x * 4, \
		&cub->tex[ind].img_ptr[cub->y_coor * cub->tex[ind].size_line + \
		cub->x_coor % 64 * cub->tex[ind].bit_pix / 8], sizeof(int));
		y++;
	}
}

void	draw_floor(t_cub3d *cub, int x)
{
	int y;

	y = cub->draw_end;
	cub->tex[4].color = 0x8A1DC4;
	while (y < cub->res_y)
	{
		ft_memmove(cub->img_ptr + 4 * cub->res_x * y + x * 4, &cub->tex[4].color, sizeof(int));
		y++;
	}
}

void	draw_ceiling(t_cub3d *cub, int x)
{
	int y;

	y = 0;
	cub->tex[5].color = 0xC41DB3;
	while (y < cub->draw_start)
	{
		ft_memmove(cub->img_ptr + 4 * cub->res_x * y + x * 4, &cub->tex[5].color, sizeof(int));
		y++;
	}
}
