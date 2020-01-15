/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:03:22 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 17:29:29 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	assign_res(t_cub3d *cub)
{
	int i;
	int j;

	i = 0;
	while (cub->buf.buffer[i] && cub->buf.buffer[i][0] != 'R')
		i++;
	j = 1;
	cub->res_x = ft_atoi(&cub->buf.buffer[i][j]);
	while (cub->buf.buffer[i][j] && cub->buf.buffer[i][j] == ' ')
		j++;
	while (cub->buf.buffer[i][j] \
		&& (cub->buf.buffer[i][j] >= '0' && cub->buf.buffer[i][j] <= '9'))
		j++;
	cub->res_y = ft_atoi(&cub->buf.buffer[i][j]);
	if (cub->res_x > 2560)
		cub->res_x = 2560;
	if (cub->res_y > 1440)
		cub->res_y = 1440;
	if (cub->res_x == 0 || cub->res_y == 0)
		display_error(cub, "Resolution not valid.\n");
}
