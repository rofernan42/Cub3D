/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:17:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/07 17:40:55 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	assign_color(t_cub3d *cub, char *line, int ind)
{
	int		i;
	int		count;
	int		color;
	char	*tmp;

	i = 0;
	count = 0;
	tmp = ft_strdup("");
	while (count < 3)
	{
		if (ft_atoi(&line[i]) > 0)
			tmp = ft_strjoin_free(tmp, \
					ft_itoa_base(ft_atoi(&line[i]), "0123456789abcdef"), 2);
		else
			tmp = ft_strjoin_free(tmp, "00", 1);
		while (line[i] && line[i] != ',')
			i++;
		i++;
		count++;
	}
	color = ft_atoi_base(tmp, "0123456789abcdef");
	cub->tex[ind].color = color;
}

static void	assign_path_tex(t_cub3d *cub, char *line, int ind)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == 'N' || line[i] == 'O' \
			|| line[i] == 'S' || line[i] == 'W' \
			|| line[i] == 'E' || line[i] == 'A' \
			|| line[i] == 'F' || line[i] == 'C' || line[i] == ' '))
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		assign_color(cub, &line[i], ind);
		cub->tex[ind].texture = 0;
	}
	else
	{
		cub->tex[ind].tex_path = ft_strtrim(&line[i], " ");
		cub->tex[ind].texture = 1;
	}
}

static void	import_tex(t_cub3d *cub, int i)
{
	if (cub->tex[i].texture == 1)
	{
		if (!(cub->tex[i].image = mlx_xpm_file_to_image(cub->mlx_ptr, \
			cub->tex[i].tex_path, &cub->tex[i].width, &cub->tex[i].height)))
		{
			cub->error = 1;
			cub->err_message = ft_strdup("Could not find image \
											or wrong image type.\n");
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
}

static void	assign_tex(t_cub3d *cub, char *line, int i)
{
	assign_path_tex(cub, line, i);
	import_tex(cub, i);
}

void		get_textures(t_cub3d *cub, t_buf *buf)
{
	int i;

	i = 0;
	while (buf->buffer[i])
	{
		if (buf->buffer[i][0] == 'S' && buf->buffer[i][1] == 'O')
			assign_tex(cub, buf->buffer[i], 0);
		if (buf->buffer[i][0] == 'N' && buf->buffer[i][1] == 'O')
			assign_tex(cub, buf->buffer[i], 1);
		if (buf->buffer[i][0] == 'E' && buf->buffer[i][1] == 'A')
			assign_tex(cub, buf->buffer[i], 2);
		if (buf->buffer[i][0] == 'W' && buf->buffer[i][1] == 'E')
			assign_tex(cub, buf->buffer[i], 3);
		if (buf->buffer[i][0] == 'F')
			assign_tex(cub, buf->buffer[i], 4);
		if (buf->buffer[i][0] == 'C')
			assign_tex(cub, buf->buffer[i], 5);
		if (buf->buffer[i][0] == 'S')
			assign_tex(cub, buf->buffer[i], 6);
		i++;
	}
	display_error(cub, buf);
}
