/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 19:16:08 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/16 16:27:10 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_missing_elem(char **str, char c, char d)
{
	int i;

	i = 0;
	while (str[i] && (str[i][0] != c || str[i][1] != d))
		i++;
	if (!str[i])
		return (0);
	return (1);
}

static int	check_double_elem(char **str, char c, char d)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i][0] == c && str[i][1] == d)
			count++;
		i++;
	}
	if (count > 1)
		return (0);
	return (1);
}

static void	check_nbr_elem(t_cub3d *cub)
{
	if (!check_missing_elem(cub->buf.buffer, 'R', ' ') \
	|| !check_missing_elem(cub->buf.buffer, 'F', ' ') \
	|| !check_missing_elem(cub->buf.buffer, 'C', ' ') \
	|| !check_missing_elem(cub->buf.buffer, 'S', ' ') \
	|| !check_missing_elem(cub->buf.buffer, 'S', 'O') \
	|| !check_missing_elem(cub->buf.buffer, 'N', 'O') \
	|| !check_missing_elem(cub->buf.buffer, 'E', 'A') \
	|| !check_missing_elem(cub->buf.buffer, 'W', 'E'))
		display_error(cub, "Information missing.\n");
	if (!check_double_elem(cub->buf.buffer, 'R', ' ') \
	|| !check_double_elem(cub->buf.buffer, 'F', ' ') \
	|| !check_double_elem(cub->buf.buffer, 'C', ' ') \
	|| !check_double_elem(cub->buf.buffer, 'S', ' ') \
	|| !check_double_elem(cub->buf.buffer, 'S', 'O') \
	|| !check_double_elem(cub->buf.buffer, 'N', 'O') \
	|| !check_double_elem(cub->buf.buffer, 'E', 'A') \
	|| !check_double_elem(cub->buf.buffer, 'W', 'E'))
		display_error(cub, "One information is double.\n");
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
	check_nbr_elem(cub);
	check_elem_order(cub);
}
