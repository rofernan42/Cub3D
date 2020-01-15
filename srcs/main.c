/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:38:22 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 12:25:32 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_map(t_cub3d *cub, t_buf *buf)
{
	create_map(cub, buf);
	adjust_map(cub);
	complete_map(cub);
	check_map(cub, buf);
	display_error(cub, buf);
}

int		main(int argc, char **argv)
{
	t_cub3d	cub;
	t_buf	buf;

	init_desc(&cub, argv[1], &buf);
	check_content(&cub, &buf);
	assign_res(&cub, &buf);
	init_map(&cub, &buf);
	if (argc == 3 && !ft_strcmp(argv[2], "--save"))
		cub.arg = 1;
	if (!(cub.mlx_ptr = mlx_init()) \
		|| !(cub.win_ptr = \
		mlx_new_window(cub.mlx_ptr, cub.res_x, cub.res_y, "cub3d")))
		return (0);
	get_textures(&cub, &buf);
	init_var(&cub);
	mlx_hook(cub.win_ptr, 17, 0L, exit_prog, &cub);
	mlx_hook(cub.win_ptr, 2, (1L << 0), key_press, &cub);
	mlx_hook(cub.win_ptr, 3, (1L << 1), key_release, &cub);
	mlx_loop_hook(cub.mlx_ptr, motion, &cub);
	mlx_loop(cub.mlx_ptr);
	free_all(&cub, &buf);
}

/*
printf("%d   %d", cub.res_x, cub.res_y);
int i = 0;
while (buf.buffer[i])
{
	printf("%s\n", buf.buffer[i]);
	i++;
}
int x = 0;
while (x < cub.map_h)
{
	printf("%s\n", cub.map[x]);
	x++;
}
*/