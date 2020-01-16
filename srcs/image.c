/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:33:52 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/16 15:45:49 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		put_image(t_cub3d *cub)
{
	raycasting(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image, 0, 0);
	if (cub->screenshot)
	{
		convert_bmp(cub);
		exit_prog(cub);
	}
}
