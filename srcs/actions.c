/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:36:21 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/09 17:02:39 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		press_key(int key, t_cub3d *cub)
{
	if (key == 126 || key == 13)
		cub->up = 1;
	if (key == 125 || key == 1)
		cub->down = 1;
	if (key == 123 || key == 0)
		cub->left = 1;
	if (key == 124 || key == 2)
		cub->right = 1;
	if (key == 48)
		cub->mov_speed = 0.12;
	if (key == 53)
		exit_prog();
	return (0);
}

int		real_key(int key, t_cub3d *cub)
{
	if (key == 126 || key == 13)
		cub->up = 0;
	if (key == 125 || key == 1)
		cub->down = 0;
	if (key == 123 || key == 0)
		cub->left = 0;
	if (key == 124 || key == 2)
		cub->right = 0;
	if (key == 48)
		cub->mov_speed = 0.05;
	return (0);
}