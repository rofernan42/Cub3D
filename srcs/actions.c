/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:36:21 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/06 15:31:08 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_press(int key, t_cub3d *cub)
{
	if (key == KEY_W || key == KEY_UP)
		cub->act.up = 1;
	if (key == KEY_S || key == KEY_DOWN)
		cub->act.down = 1;
	if (key == KEY_LEFT)
		cub->act.r_left = 1;
	if (key == KEY_A)
		cub->act.m_left = 1;
	if (key == KEY_RIGHT)
		cub->act.r_right = 1;
	if (key == KEY_D)
		cub->act.m_right = 1;
	if (key == KEY_SHIFT)
		cub->act.m_speed = 0.20;
	if (key == KEY_ESC)
		exit_prog();
	if (key == KEY_H)
	{
		if (cub->act.hud == 0)
			cub->act.hud = 1;
		else
			cub->act.hud = 0;
	}
	return (0);
}

int		key_release(int key, t_cub3d *cub)
{
	if (key == KEY_W || key == KEY_UP)
		cub->act.up = 0;
	if (key == KEY_S || key == KEY_DOWN)
		cub->act.down = 0;
	if (key == KEY_LEFT)
		cub->act.r_left = 0;
	if (key == KEY_A)
		cub->act.m_left = 0;
	if (key == KEY_RIGHT)
		cub->act.r_right = 0;
	if (key == KEY_D)
		cub->act.m_right = 0;
	if (key == KEY_SHIFT)
		cub->act.m_speed = 0.10;
	return (0);
}
