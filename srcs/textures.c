/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:17:11 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/06 20:20:23 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_textures(t_tex *tex)
{
	tex->tex_n = NULL;
	tex->tex_s = NULL;
	tex->tex_e = NULL;
	tex->tex_w = NULL;
}

void	assign_tex(t_tex *tex, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == 'N' && line[i] == 'O' \
			&& line[i] == 'S' && line[i] == 'W' \
			&& line[i] == 'E' && line[i] == 'A' \
			&& line[i] == ' ')
		i++;
	if (line[0] == 'N' && line[1] == 'O')
		tex->tex_n = ft_strdup(&line[i]);
	else if (line[0] == 'S' && line[1] == 'O')
		tex->tex_s = ft_strdup(&line[i]);
	else if (line[0] == 'W' && line[1] == 'E')
		tex->tex_w = ft_strdup(&line[i]);
	else if (line[0] == 'E' && line[1] == 'A')
		tex->tex_e = ft_strdup(&line[i]);
}