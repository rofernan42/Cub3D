/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:42:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/06 12:51:22 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display_error(t_cub3d *cub)
{
	if (cub->error == 1)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd(cub->err_message, 1);
		exit_prog();
	}
}

void	test_desc_file(void)
{
	int fd;

	if ((fd = open("desc.cub", O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd("Could not find desc.cub.\n", 1);
		close(fd);
		exit_prog();
	}
}
