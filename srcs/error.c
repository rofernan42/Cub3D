/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:42:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/07 17:06:26 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_all(t_cub3d *cub, t_buf *buf)
{
	int i;

	i = 0;
	if (buf->content)
		free(buf->content);
	if (buf->buffer)
	{
		while (buf->buffer[i])
		{
			free(buf->buffer[i]);
			i++;
		}
		free(buf->buffer);
	}
}

void	display_error(t_cub3d *cub, t_buf *buf)
{
	if (cub->error == 1)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd(cub->err_message, 1);
		free_all(cub, buf);
		exit_prog();
	}
}
