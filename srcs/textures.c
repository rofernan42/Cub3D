/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:17:11 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/09 18:36:06 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_textures(t_cub3d *cub)
{
	cub->tex.tex_path = NULL;
	cub->tex.tex_n = NULL;
	cub->tex.tex_s = NULL;
	cub->tex.tex_e = NULL;
	cub->tex.tex_w = NULL;
}

void	assign_tex(t_cub3d *cub, char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == 'N' || line[i] == 'O' \
			|| line[i] == 'S' || line[i] == 'W' \
			|| line[i] == 'E' || line[i] == 'A' \
			|| line[i] == ' '))
		i++;
	cub->tex.tex_path = ft_strdup(&line[i]);
}

void	import_tex(t_cub3d *cub)
{
	int width;
	int height;

	width = 64;
	height = 64;
	if (!(cub->tex.image = mlx_xpm_file_to_image(cub->mlx_ptr, cub->tex.tex_path, &width, &height)))
	{
		cub->error = 1;
		cub->err_message = ft_strdup("Could not convert xpm to image.\n");
		return ;
	}
	if (!(cub->tex.img_ptr = mlx_get_data_addr(cub->tex.image, &cub->tex.bit_pix, &cub->tex.size_line, &cub->tex.endian)))
	{
		cub->error = 1;
		cub->err_message = ft_strdup("Could not get data address.\n");
		return ;
	}
}
