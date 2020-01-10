/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 17:28:06 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/10 17:29:12 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_all(t_cub3d *cub, int x)
{
	draw_walls(cub, x);
	draw_floor(cub, x);
	if (cub->tex[5].tex_path \
	&& !ft_strcmp(cub->tex[5].tex_path, "textures/sky.xpm"))
		draw_sky(cub, x);
	else
		draw_ceiling(cub, x);
}
