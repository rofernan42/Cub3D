/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 19:16:08 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 17:33:31 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_missing_elem(t_cub3d *cub)
{
	int i;

	i = 0;
	while (cub->buf.buffer[i])
	{
		if (cub->buf.buffer[i][0] == 'R' || cub->buf.buffer[i][0] == 'S' \
			|| cub->buf.buffer[i][0] == 'N' || cub->buf.buffer[i][0] == 'E' \
			|| cub->buf.buffer[i][0] == 'W' || cub->buf.buffer[i][0] == 'F' \
			|| cub->buf.buffer[i][0] == 'C' || cub->buf.buffer[i][0] == 'S')
		display_error(cub, "Information missing.\n");
		i++;
	}
}

static void	check_elem_order(t_cub3d *cub)
{
	int i;

	i = 0;
	while (cub->buf.buffer[i] && cub->buf.buffer[i][0] != '1')
		i++;
	while (cub->buf.buffer[i])
	{
		if (cub->buf.buffer[i][0] == 'R' || cub->buf.buffer[i][0] == 'S' \
			|| cub->buf.buffer[i][0] == 'N' || cub->buf.buffer[i][0] == 'E' \
			|| cub->buf.buffer[i][0] == 'W' || cub->buf.buffer[i][0] == 'F' \
			|| cub->buf.buffer[i][0] == 'C' || cub->buf.buffer[i][0] == 'S')
			display_error(cub, "Map must be last in description.\n");
		i++;
	}
}

void		check_content(t_cub3d *cub)
{
	// check_missing_elem(cub, buf);
	check_elem_order(cub);
}
