/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:52:59 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/03 11:19:13 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    count_sprites(t_cub3d *cub)
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
}

void	combsort(int *order, double *dist, int amount)
{
	int gap;
	int swapped;
	int i;
	int j;

	swapped = 0;
	gap = amount;
	while (gap > 1 || swapped == 1)
	{
		gap = gap * 10 / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
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

void	init_sprites(t_cub3d *cub)
{
	int i;
	int y;
	int d;
	unsigned int color;
	int stripe;

	i = 0;
	while (i < cub->spr.nb_sprite)
	{
		cub->spr.sp_order[i] = i;
		cub->spr.sp_dist[i] = ft_power(cub->pos_x - cub->c_spr[i].x, 2) + \
							ft_power(cub->pos_y - cub->c_spr[i].y, 2);
		i++;
	}
	combsort(cub->spr.sp_order, cub->spr.sp_dist, cub->spr.nb_sprite);
	i = 0;
	while (i < cub->spr.nb_sprite)
	{
		cub->spr.sp_x = cub->c_spr[cub->spr.sp_order[i]].x - cub->pos_x;
		cub->spr.sp_y = cub->c_spr[cub->spr.sp_order[i]].y - cub->pos_y;

		cub->spr.inv_det = 1.0 / \
					(cub->plane_x * cub->dir_y - cub->plane_y * cub->dir_x);
		cub->spr.trans_x = cub->spr.inv_det * (cub->dir_y * cub->spr.sp_x - cub->dir_x * cub->spr.sp_y);
		cub->spr.trans_y = cub->spr.inv_det * (-cub->plane_y * cub->spr.sp_x + cub->plane_x * cub->spr.sp_y);
		cub->spr.sp_screen = (int)((cub->res_x / 2) * (1 + cub->spr.trans_x / cub->spr.trans_y));
		cub->spr.sp_h = abs((int)(cub->res_y / cub->spr.trans_y));
		cub->spr.draw_starty = -cub->spr.sp_h / 2 + cub->res_y / 2;
		if (cub->spr.draw_starty < 0)
			cub->spr.draw_starty = 0;
		cub->spr.draw_endy = cub->spr.sp_h / 2 + cub->res_y / 2;
		if (cub->spr.draw_endy >= cub->res_y)
			cub->spr.draw_endy = cub->res_y - 1;
		cub->spr.sp_w = abs((int)(cub->res_y / cub->spr.trans_y));
		cub->spr.draw_startx = -cub->spr.sp_w / 2 + cub->spr.sp_screen;
		if (cub->spr.draw_startx < 0)
			cub->spr.draw_startx = 0;
		cub->spr.draw_endx = cub->spr.sp_w / 2 + cub->spr.sp_screen;
		if (cub->spr.draw_endx >= cub->res_x)
			cub->spr.draw_endx = cub->res_x - 1;
		stripe = cub->spr.draw_startx;
		while (stripe < cub->spr.draw_endx)
		{
			cub->spr.tsp_x = (int)(256 * (stripe - (-cub->spr.sp_w / 2 + cub->spr.sp_screen)) * cub->tex[6].width / cub->spr.sp_w) / 256;
			if (cub->spr.trans_y > 0 && stripe > 0 && stripe < cub->res_x && cub->spr.trans_y < cub->spr.zbuffer[stripe])
			{
				y = cub->spr.draw_starty;
				while (y < cub->spr.draw_endy)
				{
					d = y * 256 - (cub->res_y + cub->spr.sp_h) * 128;
					cub->spr.tsp_y = ((d * cub->tex[6].height) / cub->spr.sp_h) / 256;
					color = cub->spr.tsp_x % cub->tex[6].width * cub->tex[6].bit_pix / 8
					+ cub->spr.tsp_y % cub->tex[6].height * cub->tex[6].size_line;
					// ft_memmove(cub->img_ptr + (cub->res_x * y + stripe) * cub->bit_pix / 8, \
					// &cub->tex[6].img_ptr[color], sizeof(int));
					y++;
				}
			}
			stripe++;
		}
		i++;
	}

}

void    sprites(t_cub3d *cub)
{
	int			x;
	int			y;
	int			ind;

	x = 0;
	ind = 0;
	count_sprites(cub);
	cub->c_spr = malloc(sizeof(*cub->c_spr) * cub->spr.nb_sprite);
	cub->spr.sp_order = malloc(sizeof(int) * cub->spr.nb_sprite);
	cub->spr.sp_dist = malloc(sizeof(double) * cub->spr.nb_sprite);
	while (x < cub->map_h)
	{
		y = 0;
		while (cub->map[x][y])
		{
			if (cub->map[x][y] == '2')
			{
				cub->c_spr[ind].x = x + 0.5;
				cub->c_spr[ind].y = y + 0.5;
				ind++;
			}
			y++;
		}
		x++;
	}
	init_sprites(cub);
}
