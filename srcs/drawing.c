/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:08:14 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/06 16:45:24 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_walls(t_cub3d *cub, int x)
{
	int col;
	int y;

	y = cub->draw_start;
	if (cub->side == 0)
		col = 0x43D52C;
	else if (cub->side == 1)
		col = 0xD5572C;
	else if (cub->side == 2)
		col = 0x2CB4D5;
	else if (cub->side == 3)
		col = 0xE9F00F;
	while (y < cub->draw_end)
	{
		ft_memcpy(cub->img_ptr + 4 * cub->res_x * y + x * 4, &col, sizeof(int));
		y++;
	}
}

void	draw_floor(t_cub3d *cub, int x)
{
	int col;
	int y;

	y = cub->draw_end;
	col = 0x8A1DC4;
	while (y < cub->res_y)
	{
		ft_memcpy(cub->img_ptr + 4 * cub->res_x * y + x * 4, &col, sizeof(int));
		y++;
	}
}

void	draw_ceiling(t_cub3d *cub, int x)
{
	int col;
	int y;

	y = 0;
	col = 0xC41DB3;
	while (y < cub->draw_start)
	{
		ft_memcpy(cub->img_ptr + 4 * cub->res_x * y + x * 4, &col, sizeof(int));
		y++;
	}
}
