/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:36:21 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/03 15:14:13 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		press_key(int key, t_cub3d *cub)
{
	if (key == 126 || key == 13)
		cub->act.up = 1;
	if (key == 125 || key == 1)
		cub->act.down = 1;
	if (key == 123)
		cub->act.r_left = 1;
	if (key == 0)
		cub->act.m_left = 1;
	if (key == 124)
		cub->act.r_right = 1;
	if (key == 2)
		cub->act.m_right = 1;
	if (key == 48)
		cub->act.m_speed = 0.2;
	if (key == 53)
		exit_prog();
	return (0);
}

int		real_key(int key, t_cub3d *cub)
{
	if (key == 126 || key == 13)
		cub->act.up = 0;
	if (key == 125 || key == 1)
		cub->act.down = 0;
	if (key == 123)
		cub->act.r_left = 0;
	if (key == 0)
		cub->act.m_left = 0;
	if (key == 124)
		cub->act.r_right = 0;
	if (key == 2)
		cub->act.m_right = 0;
	if (key == 48)
		cub->act.m_speed = 0.10;
	return (0);
}
