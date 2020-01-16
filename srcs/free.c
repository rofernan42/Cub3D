/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:24:03 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/16 15:45:27 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_buf(t_cub3d *cub)
{
	int i;

	i = 0;
	ft_strdel(&cub->buf.content);
	if (cub->buf.buffer)
	{
		while (cub->buf.buffer[i])
		{
			ft_strdel(&cub->buf.buffer[i]);
			i++;
		}
		free(cub->buf.buffer);
	}
}

static void	free_win(t_cub3d *cub)
{
	if (cub->image)
		mlx_destroy_image(cub->mlx_ptr, cub->image);
	if (cub->mlx_ptr && cub->win_ptr)
	{
		mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	}
}

static void	free_map(t_cub3d *cub)
{
	int x;

	x = 0;
	if (cub->map)
	{
		while (x < cub->map_h)
		{
			ft_strdel(&cub->map[x]);
			x++;
		}
		free(cub->map);
	}
}

static void	free_tex_spr(t_cub3d *cub)
{
	int i;

	i = 0;
	while (i < 7)
	{
		ft_strdel(&cub->tex[i].tex_path);
		if (cub->tex[i].image)
			free(cub->tex[i].image);
		if (cub->tex[i].tex_ptr)
			free(cub->tex[i].tex_ptr);
		i++;
	}
	if (cub->spr.distbuf)
		free(cub->spr.distbuf);
	if (cub->spr.sp_order)
		free(cub->spr.sp_order);
	if (cub->spr.sp_dist)
		free(cub->spr.sp_dist);
	if (cub->c_spr)
		free(cub->c_spr);
}

void		free_all(t_cub3d *cub)
{
	free_buf(cub);
	free_win(cub);
	free_map(cub);
	free_tex_spr(cub);
}
