/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:57:09 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/10 17:23:53 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	hud(t_cub3d *cub)
{
	if (cub->act.hud == 1)
	{
		mlx_string_put(cub->mlx_ptr, cub->win_ptr, 20, 10, 0xFFFFFF, \
														"W, A, S, D : move");
		mlx_string_put(cub->mlx_ptr, cub->win_ptr, 20, 30, 0xFFFFFF, \
														"<-, -> : rotate");
		mlx_string_put(cub->mlx_ptr, cub->win_ptr, 20, 50, 0xFFFFFF, \
														"SHIFT : sprint");
		mlx_string_put(cub->mlx_ptr, cub->win_ptr, 20, 70, 0xFFFFFF, \
														"H : hide help menu");
		mlx_string_put(cub->mlx_ptr, cub->win_ptr, 20, 90, 0xFFFFFF, \
														"ESC : exit");
	}
}
