/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:36:58 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/06 16:25:36 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** verifications map:
** - nb lignes >= 3
** - nb colonnes >= 3
** - des 1 tout autour du tab OK
** - verifier qu'il n y a aucun autre symbole que 0, 1, 2, N, S, E, W OK
** - verifier qu'il y a N ou S ou E ou W sur la map OK
** - verifier qu'il n y a qu'un seul N,S,E,W sur toute la map OK
*/

#include "../includes/cub3d.h"

int		check_size(t_cub3d *cub, t_map *world)
{
	int x;
	int y;

	x = 0;
	y = 0;
	world->height = Height;
	if (world->height < 3)
		return (0);
	while (x < world->height)
	{
		while (cub->map[x][y])
			y++;
		if (y < 3)
			return (0);
		y = 0;
		x++;
	}
	return (1);
}

int		check_edges(t_cub3d *cub, t_map *world)
{
	int x;
	int y;

	x = 0;
	y = 0;
	world->height = Height;
	while (cub->map[0][y] && cub->map[world->height - 1][y])
	{
		if (cub->map[0][y] != '1' || cub->map[world->height - 1][y] != '1')
			return (0);
		y++;
	}
	while (x < world->height)
	{
		if (cub->map[x][0] != '1' \
			|| cub->map[x][ft_strlen(cub->map[x]) - 1] != '1')
			return (0);
		x++;
	}
	return (1);
}

int		check_inside(t_cub3d *cub, t_map *world)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < world->height)
	{
		while (cub->map[x][y])
		{
			if (cub->map[x][y] != '0' && cub->map[x][y] != '1' \
				&& cub->map[x][y] != '2' && cub->map[x][y] != 'N' \
				&& cub->map[x][y] != 'S' && cub->map[x][y] != 'E' \
				&& cub->map[x][y] != 'W')
				return (0);
			y++;
		}
		y = 0;
		x++;
	}
	return (1);
}

int		check_position(t_cub3d *cub, t_map *world)
{
	int x;
	int y;
	int count;

	x = 0;
	y = 0;
	count = 0;
	while (x < world->height)
	{
		while (cub->map[x][y])
		{
			if (cub->map[x][y] == 'N' || cub->map[x][y] == 'S' \
				|| cub->map[x][y] == 'E' || cub->map[x][y] == 'W')
				count++;
			y++;
		}
		y = 0;
		x++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int		check_map(t_cub3d *cub, t_map *world)
{
	if (!(check_size(cub, world)))
	{
		world->err_message = ft_strdup("Map too small.\n");
		return (0);
	}
	if (!(check_edges(cub, world)))
	{
		world->err_message = ft_strdup("Map must be surrounded by 1.\n");
		return (0);
	}
	if (!(check_inside(cub, world)))
	{
		world->err_message = ft_strdup("Invalid value.\n");
		return (0);
	}
	if (!(check_position(cub, world)))
	{
		world->err_message = ft_strdup("Must have 1 position identifier.\n");
		return (0);
	}
	return (1);
}
