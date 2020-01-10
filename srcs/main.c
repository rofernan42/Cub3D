/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:38:22 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/10 20:18:28 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_map(t_cub3d *cub, t_buf *buf)
{
	create_map(cub, buf);
	adjust_map(cub);
	complete_map(cub);
	check_map(cub, buf);
}

void	set_buffer(int fd, t_buf *buf)
{
	char	*line;
	int		ret;

	buf->content = ft_strdup("");
	while ((ret = get_next_line(fd, &line)))
	{
		buf->content = ft_strjoin_free(buf->content, line, 2);
		buf->content = ft_strjoin_free(buf->content, "\n", 1);
	}
	buf->content = ft_strjoin_free(buf->content, line, 2);
}

void	init_desc(t_cub3d *cub, char *desc, t_buf *buf)
{
	int		fd;

	if ((fd = open(desc, O_RDONLY)) < 0)
	{
		cub->error = 1;
		cub->err_message = ft_strdup("Could not find map description.\n");
		close(fd);
		return ;
	}
	set_buffer(fd, buf);
	buf->buffer = ft_split_nl(buf->content);
	close(fd);
}

void	assign_res(t_cub3d *cub, t_buf *buf)
{
	int i;
	int j;

	i = 0;
	while (buf->buffer[i] && buf->buffer[i][0] != 'R')
		i++;
	j = 1;
	cub->res_x = ft_atoi(&buf->buffer[i][j]);
	while (buf->buffer[i][j] && buf->buffer[i][j] == ' ')
		j++;
	while (buf->buffer[i][j] \
		&& (buf->buffer[i][j] >= '0' && buf->buffer[i][j] <= '9'))
		j++;
	cub->res_y = ft_atoi(&buf->buffer[i][j + 1]);
	if (cub->res_x > 2560)
		cub->res_y = 2560;
	if (cub->res_y > 1440)
		cub->res_y = 1440;
	if (cub->res_x == 0 || cub->res_y == 0)
	{
		cub->error = 1;
		cub->err_message = ft_strdup("Resolution not valid.\n");
		return ;
	}
}

int	main(int argc, char **argv)
{
	t_cub3d	cub;
	t_buf	buf;

	init_desc(&cub, argv[1], &buf);
	check_content(&cub, &buf);
	int i = 0;
	while (buf.buffer[i])
	{
		printf("%s\n", buf.buffer[i]);
		i++;
	}
	assign_res(&cub, &buf);
	printf("%d  %d\n", cub.res_x, cub.res_y);
	init_map(&cub, &buf);
	int x = 0;
	while (x < cub.map_h)
	{
		printf("%s\n", cub.map[x]);
		x++;
	}
	if (!ft_strcmp(argv[2], "--save"))
		cub.arg = 1;
	if (!(cub.mlx_ptr = mlx_init()) \
		|| !(cub.win_ptr = \
		mlx_new_window(cub.mlx_ptr, cub.res_x, cub.res_y, "cub3d")))
		return (0);
	get_textures(&cub, &buf);
	init_var(&cub);
	mlx_hook(cub.win_ptr, 17, 0L, exit_prog, &cub);	/* termine le programme quand on ferme la fenetre */
	mlx_hook(cub.win_ptr, 2, (1L << 0), key_press, &cub); /* action quand une touche est pressee */
	mlx_hook(cub.win_ptr, 3, (1L << 1), key_release, &cub); /* action quand une touche est relachee */
	mlx_loop_hook(cub.mlx_ptr, motion, &cub);
	mlx_loop(cub.mlx_ptr);

	free_all(&cub, &buf);
}
