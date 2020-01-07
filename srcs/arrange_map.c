/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrange_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 18:20:30 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/07 18:32:07 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	rm_elem(char *str)
{
	int i;

	i = 0;
	if (str[i] == ' ')
	{
		while (str[i])
		{
			str[i] = str[i + 1];
			i++;
		}
	}
}

void		adjust_map(t_cub3d *cub)
{
	int x;
	int y;
	int len;

	x = 0;
	y = 0;
	cub->map_w = 0;
	while (x < cub->map_h)
	{
		while (cub->map[x][y] == ' ')
			cub->map[x][y++] = '1';
		while (cub->map[x][y])
		{
			rm_elem(&cub->map[x][y]);
			y++;
		}
		len = ft_strlen(cub->map[x]);
		if (len > cub->map_w)
			cub->map_w = len;
		y = 0;
		x++;
	}
}

void		complete_map(t_cub3d *cub)
{
	int		x;
	int		y;
	char	*endline;

	x = 0;
	while (x < cub->map_h)
	{
		y = 0;
		endline = ft_calloc(sizeof(char), \
				(cub->map_w - ft_strlen(cub->map[x]) + 1));
		ft_memset(endline, '1', cub->map_w - ft_strlen(cub->map[x]));
		cub->map[x] = ft_strjoin_free(cub->map[x], endline, 2);
		while (cub->map[x][y])
			y++;
		while (y < cub->map_w)
		{
			cub->map[x][y] = '1';
			y++;
		}
		x++;
	}
}
