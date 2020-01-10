/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:33:52 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/10 20:25:37 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		put_image(t_cub3d *cub)
{
	cub->image = mlx_new_image(cub->mlx_ptr, cub->res_x, cub->res_y);
	cub->img_ptr = mlx_get_data_addr(cub->image, &cub->bit_pix, \
									&cub->size_line, &cub->endian);
	raycasting(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image, 0, 0);
	if (cub->arg)
	{
		convert_bmp(cub);
		exit_prog();
	}
	mlx_destroy_image(cub->mlx_ptr, cub->image);
}
