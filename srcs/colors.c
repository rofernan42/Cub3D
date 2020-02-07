/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:33:14 by rofernan          #+#    #+#             */
/*   Updated: 2020/02/07 15:41:24 by rofernan         ###   ########.fr       */
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

static void	check_format(t_cub3d *cub, char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		display_error(cub, "Color format not valid (must be R,G,B).\n");
}

static void	check_byte(t_cub3d *cub, char *line, int count)
{
	int i;

	i = 0;
	if (line[0] == '\0' || line[0] == ',')
	{
		if (count == 0)
			display_error(cub, "Red value missing.\n");
		else if (count == 1)
			display_error(cub, "Green value missing.\n");
		else if (count == 2)
			display_error(cub, "Blue value missing.\n");
	}
	while (line[i] && line[i] != ',')
	{
		if (line[i] < '0' || line[i] > '9')
		{
			if (count == 0)
				display_error(cub, "Red value not valid.\n");
			else if (count == 1)
				display_error(cub, "Green value not valid.\n");
			else if (count == 2)
				display_error(cub, "Blue value not valid.\n");
		}
		i++;
	}
}

void		assign_color(t_cub3d *cub, char *line, int ind)
{
	int		i;
	int		count;
	char	*rgb[3];
	char	*color;
	int		temp;

	check_format(cub, line);
	i = 0;
	count = 0;
	while (count < 3)
	{
		temp = ft_atoi(&line[i]);
		assign_rgb(temp, &rgb[count]);
		check_byte(cub, &line[i], count);
		while (line[i] && line[i] != ',')
			i++;
		i++;
		count++;
	}
	color = ft_strjoin_free(rgb[0], rgb[1], 2);
	color = ft_strjoin_free(color, rgb[2], 2);
	cub->tex[ind].col = ft_atoi_base(color, "0123456789ABCDEF");
	ft_strdel(&color);
}
