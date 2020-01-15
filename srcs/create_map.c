/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:29:58 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 12:12:10 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_x(t_buf *buf)
{
	int		count;
	int		nb;
	int		i;

	nb = 0;
	count = 0;
	i = 0;
	while (buf->buffer[i])
	{
		nb++;
		i++;
	}
	i = 0;
	while (buf->buffer[i] && buf->buffer[i][0] != '1')
		i++;
	if (i < nb)
	{
		while (buf->buffer[i] && buf->buffer[i][0])
		{
			count++;
			i++;
		}
	}
	return (count);
}

void		create_map(t_cub3d *cub, t_buf *buf)
{
	int		x;
	int		i;

	cub->map_h = count_x(buf);
	if (cub->map_h < 3 || !(cub->map = malloc(sizeof(cub->map) * cub->map_h)))
	{
		cub->error = 1;
		cub->err_message = ft_strdup("Map error.\n");
	}
	display_error(cub, buf);
	i = 0;
	while (buf->buffer && buf->buffer[i][0] != '1')
		i++;
	x = 0;
	while (x < cub->map_h)
	{
		cub->map[x] = ft_strdup(buf->buffer[i]);
		i++;
		x++;
	}
}
