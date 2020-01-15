/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:17:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 19:02:41 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	assign_rgb(int temp, char **rgb)
{
	temp = (temp < 0 ? 0 : temp);
	temp = (temp > 255 ? 255 : temp);
	*rgb = ft_itoa_base(temp, "0123456789ABCDEF");
	if (temp < 16)
		*rgb = ft_strjoin_free("0", *rgb, 0);
}

static void	assign_color(t_cub3d *cub, char *line, int ind)
{
	int		i;
	int		count;
	char	*rgb[3];
	char	*color;
	int		temp;

	i = 0;
	count = 0;
	while (count < 3)
	{
		temp = ft_atoi(&line[i]);
		assign_rgb(temp, &rgb[count]);
		while (line[i] && line[i] != ',')
			i++;
		if (count < 2 && i == (int)ft_strlen(line))
			display_error(cub, "Could not load color.\n");
		i++;
		count++;
	}
	color = ft_strjoin_free(rgb[0], rgb[1], 2);
	color = ft_strjoin_free(color, rgb[2], 2);
	cub->tex[ind].col = ft_atoi_base(color, "0123456789ABCDEF");
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

static void	assign_tex(t_cub3d *cub, char *line, int i)
{
	assign_path_tex(cub, line, i);
	if (cub->tex[i].texture == 1)
	{
		if (!(cub->tex[i].image = mlx_xpm_file_to_image(cub->mlx_ptr, \
			cub->tex[i].tex_path, &cub->tex[i].width, &cub->tex[i].height)))
			display_error(cub, "Could not find texture.\n");
		if (!(cub->tex[i].tex_ptr = mlx_get_data_addr(cub->tex[i].image, \
			&cub->tex[i].bit_pix, &cub->tex[i].size_line, &cub->tex[i].endian)))
			display_error(cub, "Could not get data address.\n");
	}
}

void		get_textures(t_cub3d *cub)
{
	int i;

	i = 0;
	while (cub->buf.buffer[i])
	{
		if (cub->buf.buffer[i][0] == 'S' && cub->buf.buffer[i][1] == 'O')
			assign_tex(cub, cub->buf.buffer[i], 0);
		if (cub->buf.buffer[i][0] == 'N' && cub->buf.buffer[i][1] == 'O')
			assign_tex(cub, cub->buf.buffer[i], 1);
		if (cub->buf.buffer[i][0] == 'E' && cub->buf.buffer[i][1] == 'A')
			assign_tex(cub, cub->buf.buffer[i], 2);
		if (cub->buf.buffer[i][0] == 'W' && cub->buf.buffer[i][1] == 'E')
			assign_tex(cub, cub->buf.buffer[i], 3);
		if (cub->buf.buffer[i][0] == 'F')
			assign_tex(cub, cub->buf.buffer[i], 4);
		if (cub->buf.buffer[i][0] == 'C')
			assign_tex(cub, cub->buf.buffer[i], 5);
		if (cub->buf.buffer[i][0] == 'S')
			assign_tex(cub, cub->buf.buffer[i], 6);
		i++;
	}
}
