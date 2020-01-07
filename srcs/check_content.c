/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 19:16:08 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/07 19:21:11 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_missing_elem(t_cub3d *cub, t_buf *buf)
{
	int i;

	i = 0;
	while (buf->buffer[i])
	{
		if (buf->buffer[i][0] == 'R' || buf->buffer[i][0] == 'S' \
			|| buf->buffer[i][0] == 'N' || buf->buffer[i][0] == 'E' \
			|| buf->buffer[i][0] == 'W' || buf->buffer[i][0] == 'F' \
			|| buf->buffer[i][0] == 'C' || buf->buffer[i][0] == 'S')
		{
			cub->error = 1;
			cub->err_message = ft_strdup("information missing.\n");
			return ;
		}
		i++;
	}
}

static void	check_elem_order(t_cub3d *cub, t_buf *buf)
{
	int i;

	i = 0;
	while (buf->buffer[i] && buf->buffer[i][0] != '1')
		i++;
	while (buf->buffer[i])
	{
		if (buf->buffer[i][0] == 'R' || buf->buffer[i][0] == 'S' \
			|| buf->buffer[i][0] == 'N' || buf->buffer[i][0] == 'E' \
			|| buf->buffer[i][0] == 'W' || buf->buffer[i][0] == 'F' \
			|| buf->buffer[i][0] == 'C' || buf->buffer[i][0] == 'S')
		{
			cub->error = 1;
			cub->err_message = ft_strdup("Map must be last in description.\n");
			return ;
		}
		i++;
	}
}

void		check_content(t_cub3d *cub, t_buf *buf)
{
	// check_missing_elem(cub, buf);
	check_elem_order(cub, buf);
	display_error(cub, buf);
}
