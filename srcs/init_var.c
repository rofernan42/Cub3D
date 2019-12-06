/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 12:37:12 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/06 15:21:47 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_cub(t_cub3d *cub)
{
	cub->time = 0;
	cub->prev_time = 0;
	cub->mov_speed = 0.05;
	cub->rot_speed = 0.05;
	cub->up = 0;
	cub->down = 0;
	cub->left = 0;
	cub->right = 0;
}

void	init_position(t_cub3d *cub)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < Width)
	{
		while (y < Height)
		{
			if (cub->map[x][y] == 'N' || cub->map[x][y] == 'S' \
			|| cub->map[x][y] == 'E' || cub->map[x][y] == 'W')
			{
				cub->pos_x = x;
				cub->pos_y = y;
			}
			y++;
		}
		y = 0;
		x++;
	}
}

void	init_direction(t_cub3d *cub)
{
	if (cub->map[(int)cub->pos_x][(int)cub->pos_y] == 'N')
	{
		cub->dir_x = -1;
		cub->dir_y = 0;
	}
	else if (cub->map[(int)cub->pos_x][(int)cub->pos_y] == 'S')
	{
		cub->dir_x = 1;
		cub->dir_y = 0;
	}
	else if (cub->map[(int)cub->pos_x][(int)cub->pos_y] == 'E')
	{
		cub->dir_x = 0;
		cub->dir_y = 1;
	}
	else if (cub->map[(int)cub->pos_x][(int)cub->pos_y] == 'W')
	{
		cub->dir_x = 0;
		cub->dir_y = -1;
	}
}

void	init_plane(t_cub3d *cub)
{
	if (cub->map[(int)cub->pos_x][(int)cub->pos_y] == 'N' \
	|| cub->map[(int)cub->pos_x][(int)cub->pos_y] == 'S')
	{
		cub->plane_x = -cub->dir_y * tan(M_PI * 33 / 180);
		cub->plane_y = -cub->dir_x * tan(M_PI * 33 / 180);
	}
	else if (cub->map[(int)cub->pos_x][(int)cub->pos_y] == 'E' \
	|| cub->map[(int)cub->pos_x][(int)cub->pos_y] == 'W')
	{
		cub->plane_x = cub->dir_y * tan(M_PI * 33 / 180);
		cub->plane_y = cub->dir_x * tan(M_PI * 33 / 180);
	}
}

void	init_var(t_cub3d *cub)
{
	init_cub(cub);
	init_position(cub);
	init_direction(cub);
	init_plane(cub);
}

/*
** (M_PI * 33 / 180) rad = (66 / 2) deg
*/
