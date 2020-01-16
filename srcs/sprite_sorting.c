/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:25:43 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/16 16:43:37 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		count_sprites(t_cub3d *cub)
{
	int x;
	int y;

	x = 0;
	cub->spr.nb_sprite = 0;
	while (x < cub->map_h)
	{
		y = 0;
		while (cub->map[x][y])
		{
			if (cub->map[x][y] == '2')
				cub->spr.nb_sprite++;
			y++;
		}
		x++;
	}
	cub->c_spr = malloc(sizeof(*cub->c_spr) * cub->spr.nb_sprite);
	cub->spr.sp_order = malloc(sizeof(int) * cub->spr.nb_sprite);
	cub->spr.sp_dist = malloc(sizeof(double) * cub->spr.nb_sprite);
}

void		create_sorting(t_cub3d *cub)
{
	int i;

	i = 0;
	while (i < cub->spr.nb_sprite)
	{
		cub->spr.sp_order[i] = i;
		cub->spr.sp_dist[i] = ft_power(cub->pos_x - cub->c_spr[i].x, 2) + \
							ft_power(cub->pos_y - cub->c_spr[i].y, 2);
		i++;
	}
}

static void	calc_gap(int *gap)
{
	*gap = *gap * 10 / 13;
	if (*gap == 9 || *gap == 10)
		*gap = 11;
	if (*gap < 1)
		*gap = 1;
}

void		sort_sprites(int *order, double *dist, int amount)
{
	int gap;
	int swapped;
	int i;
	int j;

	swapped = 0;
	gap = amount;
	while (gap > 1 || swapped == 1)
	{
		calc_gap(&gap);
		swapped = 0;
		i = 0;
		while (i < amount - gap)
		{
			j = i + gap;
			if (dist[i] < dist[j])
			{
				ft_swap_dbl(&dist[i], &dist[j]);
				ft_swap_int(&order[i], &order[j]);
				swapped = 1;
			}
			i++;
		}
	}
}
