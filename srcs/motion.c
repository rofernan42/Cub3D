/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 10:20:01 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/06 17:25:45 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move(t_cub3d *cub)
{
	if (cub->up == 1)
	{
		if (cub->map[(int)(cub->pos_x + cub->dir_x * cub->mov_speed)]\
					[(int)(cub->pos_y)] != '1')
			cub->pos_x += cub->dir_x * cub->mov_speed;
		if (cub->map[(int)(cub->pos_x)]\
					[(int)(cub->pos_y + cub->dir_y * cub->mov_speed)] != '1')
			cub->pos_y += cub->dir_y * cub->mov_speed;
	}
	if (cub->down == 1)
	{
		if (cub->map[(int)(cub->pos_x - cub->dir_x * cub->mov_speed)]\
					[(int)(cub->pos_y)] != '1')
			cub->pos_x -= cub->dir_x * cub->mov_speed;
		if (cub->map[(int)(cub->pos_x)]\
					[(int)(cub->pos_y - cub->dir_y * cub->mov_speed)] != '1')
			cub->pos_y -= cub->dir_y * cub->mov_speed;
	}
}

static void	turn_left(t_cub3d *cub)
{
	if (cub->left == 1)
	{
		cub->olddir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(cub->rot_speed) \
					- cub->dir_y * sin(cub->rot_speed);
		cub->dir_y = cub->olddir_x * sin(cub->rot_speed) \
					+ cub->dir_y * cos(cub->rot_speed);
		cub->oldplane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(cub->rot_speed) \
					- cub->plane_y * sin(cub->rot_speed);
		cub->plane_y = cub->oldplane_x * sin(cub->rot_speed) \
					+ cub->plane_y * cos(cub->rot_speed);
	}
}

static void	turn_right(t_cub3d *cub)
{
	if (cub->right == 1)
	{
		cub->olddir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(-cub->rot_speed) \
					- cub->dir_y * sin(-cub->rot_speed);
		cub->dir_y = cub->olddir_x * sin(-cub->rot_speed) \
					+ cub->dir_y * cos(-cub->rot_speed);
		cub->oldplane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(-cub->rot_speed) \
					- cub->plane_y * sin(-cub->rot_speed);
		cub->plane_y = cub->oldplane_x * sin(-cub->rot_speed) \
					+ cub->plane_y * cos(-cub->rot_speed);
	}
}

// static void	turn_up(t_cub3d *cub)
// {
// 	if (cub->t_up == 1)
// 	{
// 		cub->olddir_x = cub->dir_x;
// 		cub->dir_x = cub->dir_x * cos(-cub->rot_speed) \
// 					- cub->dir_y * sin(-cub->rot_speed);
// 		cub->dir_y = cub->olddir_x * sin(-cub->rot_speed) \
// 					+ cub->dir_y * cos(-cub->rot_speed);
// 		cub->oldplane_x = cub->plane_x;
// 		cub->plane_x = cub->plane_x * cos(-cub->rot_speed) \
// 					- cub->plane_y * sin(-cub->rot_speed);
// 		cub->plane_y = cub->oldplane_x * sin(-cub->rot_speed) \
// 					+ cub->plane_y * cos(-cub->rot_speed);
// 	}
// }

int			motion(t_cub3d *cub)
{
	move(cub);
	turn_left(cub);
	turn_right(cub);
	raycasting(cub);
	return (0);
}
