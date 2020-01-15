/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:42:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 14:37:48 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display_error(t_cub3d *cub, t_buf *buf)
{
	if (cub->error == 1)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd(cub->err_message, 1);
		free_all(cub, buf);
		exit_prog();
	}
}
