/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 10:20:01 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/08 14:59:19 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move(t_cub3d *cub)
{
	if (cub->act.up == 1)
	{
		if (cub->map[(int)(cub->pos_x + cub->dir_x * cub->act.m_speed)]\
					[(int)(cub->pos_y)] == '0')
			cub->pos_x += cub->dir_x * cub->act.m_speed;
		if (cub->map[(int)(cub->pos_x)]\
					[(int)(cub->pos_y + cub->dir_y * cub->act.m_speed)] == '0')
			cub->pos_y += cub->dir_y * cub->act.m_speed;
	}
	if (cub->act.down == 1)
	{
		if (cub->map[(int)(cub->pos_x - cub->dir_x * cub->act.m_speed)]\
					[(int)(cub->pos_y)] == '0')
			cub->pos_x -= cub->dir_x * cub->act.m_speed;
		if (cub->map[(int)(cub->pos_x)]\
					[(int)(cub->pos_y - cub->dir_y * cub->act.m_speed)] == '0')
			cub->pos_y -= cub->dir_y * cub->act.m_speed;
	}
}

static void	move_side(t_cub3d *cub)
{
	if (cub->act.m_left == 1)
	{
		if (cub->map[(int)(cub->pos_x - cub->dir_y * cub->act.m_speed)]\
					[(int)(cub->pos_y)] == '0')
			cub->pos_x -= cub->dir_y * cub->act.m_speed;
		if (cub->map[(int)(cub->pos_x)]\
					[(int)(cub->pos_y + cub->dir_x * cub->act.m_speed)] == '0')
			cub->pos_y += cub->dir_x * cub->act.m_speed;
	}
	if (cub->act.m_right == 1)
	{
		if (cub->map[(int)(cub->pos_x + cub->dir_y * cub->act.m_speed)]\
					[(int)(cub->pos_y)] == '0')
			cub->pos_x += cub->dir_y * cub->act.m_speed;
		if (cub->map[(int)(cub->pos_x)]\
					[(int)(cub->pos_y - cub->dir_x * cub->act.m_speed)] == '0')
			cub->pos_y -= cub->dir_x * cub->act.m_speed;
	}
}

static void	turn_left(t_cub3d *cub)
{
	if (cub->act.r_left == 1)
	{
		cub->olddir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(cub->act.r_speed) \
					- cub->dir_y * sin(cub->act.r_speed);
		cub->dir_y = cub->olddir_x * sin(cub->act.r_speed) \
					+ cub->dir_y * cos(cub->act.r_speed);
		cub->oldplane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(cub->act.r_speed) \
					- cub->plane_y * sin(cub->act.r_speed);
		cub->plane_y = cub->oldplane_x * sin(cub->act.r_speed) \
					+ cub->plane_y * cos(cub->act.r_speed);
	}
}

static void	turn_right(t_cub3d *cub)
{
	if (cub->act.r_right == 1)
	{
		cub->olddir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(-cub->act.r_speed) \
					- cub->dir_y * sin(-cub->act.r_speed);
		cub->dir_y = cub->olddir_x * sin(-cub->act.r_speed) \
					+ cub->dir_y * cos(-cub->act.r_speed);
		cub->oldplane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(-cub->act.r_speed) \
					- cub->plane_y * sin(-cub->act.r_speed);
		cub->plane_y = cub->oldplane_x * sin(-cub->act.r_speed) \
					+ cub->plane_y * cos(-cub->act.r_speed);
	}
}

int			motion(t_cub3d *cub)
{
	move(cub);
	move_side(cub);
	turn_left(cub);
	turn_right(cub);
	raycasting(cub);
	hud(cub);
	return (0);
}
