/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:29:58 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/06 19:33:11 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int		count_x(int fd, t_cub3d *cub)
{
	int		ret;
	int		count;
	char	*line;

	count = 0;
	get_next_line(fd, &line);
	while ((ret = get_next_line(fd, &line)))
	{
		if (line[0] == '1')
		{
			count++;
			break ;
		}
		free(line);
	}
	while ((ret = get_next_line(fd, &line)))
	{
		count++;
		free(line);
	}
	count++;
	return (count);
}

void	create_map(int fd, t_cub3d *cub, t_map *world)
{
	int		x;
	int		ret;
	char	*line;

	x = 0;
	while ((ret = get_next_line(fd, &line)) && line[0] != '1')
		ft_strdel(&line);
	while (x < world->height)
	{
		cub->map[x] = ft_strdup(line);
		x++;
		ft_strdel(&line);
		get_next_line(fd, &line);
	}
	ft_strdel(&line);
}

void	adjust_map(t_cub3d *cub, t_map *world)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < world->height)
	{
		while (cub->map[x][y])
		{
			if (cub->map[x][y] == ' ')
			{
				while(cub->map[x][y])
				{
					cub->map[x][y] = cub->map[x][y + 1];
					y++;
				}
				y = 0;
			}
			y++;
		}
		y = 0;
		x++;
	}
}
