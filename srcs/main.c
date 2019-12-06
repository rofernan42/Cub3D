/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:38:22 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/06 16:03:59 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		exit_prog(void)
{
	exit(1);
	return (0);
}

int	read_desc(int fd, t_cub3d *cub)
{
	char	*line;
	int		ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((ret = get_next_line(fd, &line)) && line[0] != '1')
	{
		if (line[0] == 'R')
		{
			i = 1;
			cub->res_x = ft_atoi(&line[1]);
			while (line[i] && line[i] == ' ')
				i++;
			while (line[i] && (line[i] >= '0' && line[i] <= '9'))
				i++;
			cub->res_y = ft_atoi(&line[i]);
		}
		free(line);
	}
	
	// while ()
	// while (ret = get_next_line(fd, &line))
	// {
	// 	if (line[0] == '1')
	// 	{
	// 		cub->map[j] = ft_strdup(line);
	// 		j++;
	// 	}
	// 	free(line);
	// }
	return (1);
}

int press_key(int key, t_cub3d *cub)
{
	if (key == 126 || key == 13)
		cub->up = 1;
	if (key == 125 || key == 1)
		cub->down = 1;
	if (key == 123 || key == 0)
		cub->left = 1;
	if (key == 124 || key == 2)
		cub->right = 1;
	if (key == 48)
		cub->mov_speed = 0.12;
	return (0);
}

int real_key(int key, t_cub3d *cub)
{
	if (key == 126 || key == 13)
		cub->up = 0;
	if (key == 125 || key == 1)
		cub->down = 0;
	if (key == 123 || key == 0)
		cub->left = 0;
	if (key == 124 || key == 2)
		cub->right = 0;
	if (key == 48)
		cub->mov_speed = 0.05;
	return (0);
}

int	main(void)
{
	t_cub3d	cub;
	t_map	world;
	int		fd;
	
	fd = open("desc.cub", O_RDONLY);
	read_desc(fd, &cub);

	cub.map[0] = "1111111111";
	cub.map[1] = "1001111001";
	cub.map[2] = "1000000001";
	cub.map[3] = "1000000001";
	cub.map[4] = "10000N0011";
	cub.map[5] = "1000000001";
	cub.map[6] = "1000002001";
	cub.map[7] = "1100001111";
	cub.map[8] = "1100001111";
	cub.map[9] = "1111111111";

	if (!(check_map(&cub, &world)))
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd("Invalid map\n", 1);
		return (0);
	}
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.res_x, cub.res_y, "cub3d");

	mlx_hook(cub.win_ptr, 17, 0L, exit_prog, &cub);	/* termine le programme quand on ferme la fenetre */
	mlx_hook(cub.win_ptr, 2, (1L<<0), press_key, &cub); /* action quand une touche est pressee */
	mlx_hook(cub.win_ptr, 3, (1L<<1), real_key, &cub); /* action quand une touche est relachee */
	
	init_var(&cub);
	printf("%f  %f\n", cub.pos_x, cub.pos_y);
	mlx_loop_hook(cub.mlx_ptr, motion, &cub);
	mlx_loop(cub.mlx_ptr);
}
