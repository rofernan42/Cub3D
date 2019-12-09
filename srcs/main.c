/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:38:22 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/09 16:09:04 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		exit_prog(void)
{
	exit(1);
	return (0);
}

void	assign_res(t_cub3d *cub, char *line)
{
	int i;

	if (line[1])
	{
		i = 1;
		cub->res_x = ft_atoi(&line[1]);
		while (line[i] && line[i] == ' ')
			i++;
		while (line[i] && (line[i] >= '0' && line[i] <= '9'))
			i++;
		cub->res_y = ft_atoi(&line[i]);
	}
	else
	{
		cub->res_x = 0;
		cub->res_y = 0;
	}
}



void	read_desc(int fd, t_cub3d *cub)
{
	char	*line;
	int		ret;

	init_textures(cub);
	while ((ret = get_next_line(fd, &line)) && line[0] != '1')
	{
		if (line[0])
		{
			if (line[0] == 'R')
				assign_res(cub, line);
			if ((line[0] == 'N' && line[1] == 'O') \
			|| (line[0] == 'S' && line[1] == 'O') \
			|| (line[0] == 'W' && line[1] == 'E') \
			|| (line[0] == 'E' && line[1] == 'A'))
			{
				assign_tex(cub, line);
				// import_tex(cub);
			}
			// if (line[0] == 'S')
			// if (line[0] == 'F')
			// if (line[0] == 'C')
		}
		free(line);
	}
	while ((ret = get_next_line(fd, &line)))
		free(line);
	get_next_line(fd, &line);
	free(line);
}

int		init_desc(t_cub3d *cub)
{
	int fd;

	fd = open("desc.cub", O_RDONLY);
	read_desc(fd, cub);
	close(fd);
	fd = open("desc.cub", O_RDONLY);
	count_x(fd, cub);
	if (!(cub->map = malloc(sizeof(cub->map) * cub->map_h)))
		return (0);
	close(fd);
	fd = open("desc.cub", O_RDONLY);
	create_map(fd, cub);
	close(fd);
	adjust_map(cub);
	complete_map(cub);
	return (1);
}

int		check_error(t_cub3d *cub)
{
	if (cub->res_x == 0 || cub->res_y == 0)
		return (0);
	return (1);
}

int	main(void)
{
	t_cub3d	cub;
	t_tex	tex;

	init_desc(&cub);
	printf("%s\n", cub.tex.tex_n);
	printf("%s\n", cub.tex.image);
	printf("int %lu    char %lu    char* %lu\n", sizeof(int), sizeof(char), sizeof(char*));
	// TEMP: affichage map
	int x = 0;
	while (x < cub.map_h)
	{
		printf("%s\n", cub.map[x]);
		x++;
	}

	check_map(&cub);
	if (cub.error == 1)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd(cub.err_message, 1);
		return (0);
	}
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.res_x, cub.res_y, "cub3d");

	mlx_hook(cub.win_ptr, 17, 0L, exit_prog, &cub);	/* termine le programme quand on ferme la fenetre */
	mlx_hook(cub.win_ptr, 2, (1L<<0), press_key, &cub); /* action quand une touche est pressee */
	mlx_hook(cub.win_ptr, 3, (1L<<1), real_key, &cub); /* action quand une touche est relachee */

	init_var(&cub);
	// printf("%f  %f\n", cub.pos_x, cub.pos_y);
	mlx_loop_hook(cub.mlx_ptr, motion, &cub);
	mlx_loop(cub.mlx_ptr);
}
