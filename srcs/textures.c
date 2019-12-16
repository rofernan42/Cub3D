/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:17:11 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/16 17:32:04 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	assign_tex(t_cub3d *cub, char *line, int ind)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == 'N' || line[i] == 'O' \
			|| line[i] == 'S' || line[i] == 'W' \
			|| line[i] == 'E' || line[i] == 'A' \
			|| line[i] == 'F' || line[i] == 'C'))
		i++;
	cub->tex[ind].tex_path = ft_strtrim(&line[i], " ");
}

void	import_tex(t_cub3d *cub, int i)
{
	if (!(cub->tex[i].image = mlx_xpm_file_to_image(cub->mlx_ptr, \
		cub->tex[i].tex_path, &cub->tex[i].width, &cub->tex[i].height)))
	{
		cub->error = 1;
		cub->err_message = ft_strdup("Could not convert xpm to image.\n");
		return ;
	}
	if (!(cub->tex[i].img_ptr = mlx_get_data_addr(cub->tex[i].image, \
		&cub->tex[i].bit_pix, &cub->tex[i].size_line, &cub->tex[i].endian)))
	{
		cub->error = 1;
		cub->err_message = ft_strdup("Could not get data address.\n");
		return ;
	}
}
