/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:38:22 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 19:05:29 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init(t_cub3d *cub)
{
	ft_memset(&cub->buf, 0, sizeof(t_buf));
	ft_memset(&cub->tex, 0, sizeof(t_tex) * 7);
	ft_memset(&cub->act, 0, sizeof(t_action));
	ft_memset(&cub->spr, 0, sizeof(t_sprite));
}

void	init_map(t_cub3d *cub)
{
	create_map(cub);
	adjust_map(cub);
	complete_map(cub);
	check_map(cub);
}

int		main(int argc, char **argv)
{
	t_cub3d	cub;

	if (argc > 1)
	{
		init(&cub);
		init_desc(&cub, argv[1]);
		check_content(&cub);
		assign_res(&cub);
		init_map(&cub);
		if (argc == 3 && !ft_strcmp(argv[2], "--save"))
			cub.screenshot = 1;
		if (!(cub.mlx_ptr = mlx_init()) \
			|| !(cub.win_ptr = \
			mlx_new_window(cub.mlx_ptr, cub.res_x, cub.res_y, "cub3d")))
			return (0);
		get_textures(&cub);
		init_var(&cub);
		mlx_hook(cub.win_ptr, 17, 0L, exit_prog, &cub);
		mlx_hook(cub.win_ptr, 2, (1L << 0), key_press, &cub);
		mlx_hook(cub.win_ptr, 3, (1L << 1), key_release, &cub);
		mlx_loop_hook(cub.mlx_ptr, motion, &cub);
		mlx_loop(cub.mlx_ptr);
	}
	else
		ft_putstr_fd("Please select descriptor file.\n", 1);
	return (0);
}

/*
printf("%d   %d", cub.res_x, cub.res_y);
int i = 0;
while (cub.buf.buffer[i])
{
	printf("%s\n", cub.buf.buffer[i]);
	i++;
}
printf("%s\n", cub.buf.buffer[i]);
int x = 0;
while (x < cub.map_h)
{
	printf("%s\n", cub.map[x]);
	x++;
}
*/