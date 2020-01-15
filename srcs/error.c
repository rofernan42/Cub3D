/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:42:11 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 19:03:28 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display_error(t_cub3d *cub, char *err_message)
{
	ft_putstr_fd("ERROR\n", 1);
	ft_putstr_fd(err_message, 1);
	exit_prog(cub);
}
