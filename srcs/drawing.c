/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:08:14 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/09 18:10:36 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_walls(t_cub3d *cub, int x)
{
	int col;
	int y;

	y = cub->draw_start;
	if (cub->side == 0)
	{
		// if (!cub->tex.tex_s)
			cub->tex.color = 0x43D52C;
	}
	else if (cub->side == 1)
	{
		// if (!cub->tex.tex_n)
			cub->tex.color = 0xD5572C;
	}
	else if (cub->side == 2)
	{
		// if (!cub->tex.tex_e)
			cub->tex.color = 0x2CB4D5;
	}
	else if (cub->side == 3)
	{
		// if (!cub->tex.tex_w)
			cub->tex.color = 0xE9F00F;
	}
	while (y < cub->draw_end)
	{
		ft_memmove(cub->img_ptr + 4 * cub->res_x * y + x * 4, &cub->tex.color, sizeof(int));
		y++;
	}
}

void	draw_floor(t_cub3d *cub, int x)
{
	int y;

	y = cub->draw_end;
	cub->tex.color = 0x8A1DC4;
	while (y < cub->res_y)
	{
		ft_memmove(cub->img_ptr + 4 * cub->res_x * y + x * 4, &cub->tex.color, sizeof(int));
		y++;
	}
}

void	draw_ceiling(t_cub3d *cub, int x)
{
	int y;

	y = 0;
	cub->tex.color = 0xC41DB3;
	while (y < cub->draw_start)
	{
		ft_memmove(cub->img_ptr + 4 * cub->res_x * y + x * 4, &cub->tex.color, sizeof(int));
		y++;
	}
}
