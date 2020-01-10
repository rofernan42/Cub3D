/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 11:23:05 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/10 17:06:29 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_color(t_cub3d *cub, int ind, int x, int y)
{
	if (x >= 0 && x < cub->tex[ind].width && y >= 0 && y < cub->tex[ind].height)
	{
		cub->tex[ind].color = \
		*(int*)(cub->tex[ind].tex_ptr + \
		(x * cub->tex[ind].bit_pix / 8 + y * cub->tex[ind].size_line));
	}
	else
		cub->tex[ind].color = 0x0;
	
}

void	color_dist(t_cub3d *cub, int ind, double dist)
{
	if (dist > 2.5)
	{
		cub->tex[ind].color = \
		(((int)(((cub->tex[ind].color & 0xFF0000) >> 16) / (dist / 2.5)) << 16)|\
		((int)(((cub->tex[ind].color & 0x00FF00) >> 8) / (dist / 2.5)) << 8)|\
		(int)((cub->tex[ind].color & 0x0000FF) / (dist / 2.5)));
	}
}

void	draw_pix(t_cub3d *cub, int ind, int x, int y)
{
	if (x >= 0 && x < cub->res_x && y >= 0 && y < cub->res_y)
		*(int*)(cub->img_ptr + (cub->res_x * y + x) * cub->bit_pix / 8) = \
		cub->tex[ind].color;
}
