/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:52:59 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/10 14:22:05 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	sprite_position(t_cub3d *cub, int i)
{
	cub->spr.sp_x = cub->c_spr[cub->spr.sp_order[i]].x - cub->pos_x;
	cub->spr.sp_y = cub->c_spr[cub->spr.sp_order[i]].y - cub->pos_y;
	cub->spr.inv_det = 1.0 / \
				(cub->plane_x * cub->dir_y - cub->plane_y * cub->dir_x);
	cub->spr.trans_x = cub->spr.inv_det * \
				(cub->dir_y * cub->spr.sp_x - cub->dir_x * cub->spr.sp_y);
	cub->spr.trans_y = cub->spr.inv_det * \
				(-cub->plane_y * cub->spr.sp_x + cub->plane_x * cub->spr.sp_y);
	cub->spr.sp_screen = (int)((cub->res_x / 2) * \
				(1.0 + cub->spr.trans_x / cub->spr.trans_y));
}

static void	sprite_dimensions(t_cub3d *cub)
{
	cub->spr.sp_h = abs((int)(cub->res_y / cub->spr.trans_y));
	cub->spr.sp_w = abs((int)(cub->res_y / cub->spr.trans_y));
	cub->spr.draw_starty = -cub->spr.sp_h / 2 + cub->res_y / 2;
	if (cub->spr.draw_starty < 0)
		cub->spr.draw_starty = 0;
	cub->spr.draw_endy = cub->spr.sp_h / 2 + cub->res_y / 2;
	if (cub->spr.draw_endy >= cub->res_y)
		cub->spr.draw_endy = cub->res_y - 1;
	cub->spr.draw_startx = -cub->spr.sp_w / 2 + cub->spr.sp_screen;
	if (cub->spr.draw_startx < 0)
		cub->spr.draw_startx = 0;
	cub->spr.draw_endx = cub->spr.sp_w / 2 + cub->spr.sp_screen;
	if (cub->spr.draw_endx >= cub->res_x)
		cub->spr.draw_endx = cub->res_x - 1;
}

static void	draw_sprites(t_cub3d *cub, int x, int i)
{
	int y;
	int d;

	y = cub->spr.draw_starty;
	while (y < cub->spr.draw_endy)
	{
		d = y * 256 - (cub->res_y - cub->spr.sp_h) * 128;
		cub->spr.tsp_y = ((d * cub->tex[6].height) / cub->spr.sp_h) / 256;
		get_color(cub, 6, cub->spr.tsp_x, cub->spr.tsp_y);
		color_dist(cub, 6, cub->spr.sp_dist[i]);
		if (cub->tex[6].color != 0x0 \
			&& cub->spr.trans_y < cub->spr.distbuf[x])
			draw_pix(cub, 6, x, y);
		y++;
	}
}

static void	init_sprites(t_cub3d *cub)
{
	int i;
	int x;

	create_sorting(cub);
	sort_sprites(cub->spr.sp_order, cub->spr.sp_dist, cub->spr.nb_sprite);
	i = 0;
	while (i < cub->spr.nb_sprite)
	{
		sprite_position(cub, i);
		sprite_dimensions(cub);
		x = cub->spr.draw_startx;
		while (x < cub->spr.draw_endx && x < cub->res_x)
		{
			cub->spr.tsp_x = (int)(256 * \
				(x - (-cub->spr.sp_w / 2 + cub->spr.sp_screen)) * \
				cub->tex[6].width / cub->spr.sp_w) / 256;
			if (cub->spr.trans_y > 0)
				draw_sprites(cub, x, i);
			x++;
		}
		i++;
	}
}

void		sprites(t_cub3d *cub)
{
	int x;
	int y;
	int ind;

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
				cub->c_spr[ind++].y = y + 0.5;
			}
			y++;
		}
		x++;
	}
	init_sprites(cub);
}
