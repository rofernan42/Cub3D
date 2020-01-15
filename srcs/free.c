/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:24:03 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 15:24:57 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_buf(t_buf *buf)
{
	int i;

	i = 0;
	ft_strdel(&buf->content);
	if (buf->buffer)
	{
		while (buf->buffer[i])
			ft_strdel(&buf->buffer[i++]);
		free(buf->buffer);
	}
}

static void	free_tex_spr(t_cub3d *cub)
{
	int i;

	i = 0;
	while (i < 7)
	{
		ft_strdel(&cub->tex[i].tex_path);
		ft_strdel((char**)&cub->tex[i].image);
		ft_strdel((char**)&cub->tex[i].tex_ptr);
	}
	i = 0;
	while (i < cub->spr.nb_sprite)
	{
		if (cub->spr.distbuf)
			free(cub->spr.distbuf);
		if (cub->spr.sp_order)
			free(cub->spr.sp_order);
		if (cub->spr.sp_dist)
			free(cub->spr.sp_dist);
	}
	if (cub->c_spr)
		free(cub->c_spr);
}

static void	free_cub(t_cub3d *cub)
{
	int i;

	i = 0;
	if (cub->map)
	{
		while (cub->map[i])
			ft_strdel(&cub->map[i++]);
		free(cub->map);
	}
	ft_strdel((char**)&cub->mlx_ptr);
	ft_strdel((char**)&cub->win_ptr);
	ft_strdel((char**)&cub->image);
	ft_strdel((char**)&cub->img_ptr);
	ft_strdel(&cub->err_message);
}

void		free_all(t_cub3d *cub, t_buf *buf)
{
	free_buf(buf);
	free_tex_spr(cub);
	free_cub(cub);
}
