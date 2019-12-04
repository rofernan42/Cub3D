/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:38:22 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/04 18:42:33 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		cub->move_speed = 0.12;
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
		cub->move_speed = 0.05;
	return (0);
}

#define mapWidth 10
#define mapHeight 10

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1},
  {1,0,0,1,1,1,1,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,1,1,1},
  {1,1,0,0,0,0,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1}
};

void	init_cub(t_cub3d *cub)
{
	cub->pos_x = 6;
	cub->pos_y = 3;
	cub->dir_x = 0;
	cub->dir_y = 1;
	cub->plane_x = 0.66;
	cub->plane_y = 0;
	cub->time = 0;
	cub->prev_time = 0;
	cub->move_speed = 0.05;
	cub->rot_speed = 0.05;
	cub->up = 0;
	cub->down = 0;
	cub->left = 0;
	cub->right = 0;
}

void	raycasting(t_cub3d *cub)
{
	int x;
	int y;
	int color;

	x = 0;
	cub->image = mlx_new_image(cub->mlx_ptr, cub->res_x, cub->res_y);
	cub->img_ptr = mlx_get_data_addr(cub->image, &cub->bpp, &cub->sl, &cub->endian);
	while (x < cub->res_x)
    {
		cub->cam_plane = (double)(2 * x / (double)cub->res_x) - 1;
		cub->raydir_x = cub->dir_x + cub->plane_x * cub->cam_plane;
		cub->raydir_y = cub->dir_y + cub->plane_y * cub->cam_plane;
		cub->map_x = cub->pos_x;
		cub->map_y = cub->pos_y;
		cub->delta_dx = fabs(1 / cub->raydir_x);
		cub->delta_dy = fabs(1 / cub->raydir_y);
		if (cub->raydir_x < 0)
		{
			cub->step_x = -1;
			cub->side_dx = (cub->pos_x - cub->map_x) * cub->delta_dx;
		}
		else
		{
			cub->step_x = 1;
			cub->side_dx = (cub->map_x + 1.0 - cub->pos_x) * cub->delta_dx;
		}
		if (cub->raydir_y < 0)
		{
			cub->step_y = -1;
			cub->side_dy = (cub->pos_y - cub->map_y) * cub->delta_dy;
		}
		else
		{
			cub->step_y = 1;
			cub->side_dy = (cub->map_y + 1.0 - cub->pos_y) * cub->delta_dy;
		}
		cub->wall_hit = 0;
		while (cub->wall_hit == 0)
		{
			if (cub->side_dx < cub->side_dy)
			{
				cub->side_dx = cub->side_dx + cub->delta_dx;
				cub->map_x = cub->map_x + cub->step_x;
				cub->side = 0;
			}
			else
			{
				cub->side_dy = cub->side_dy + cub->delta_dy;
				cub->map_y = cub->map_y + cub->step_y;
				cub->side = 1;
			}
			if (worldMap[cub->map_x][cub->map_y] > 0)
				cub->wall_hit = 1;
		}
		if (cub->side == 0)
			cub->wall_dist = (cub->map_x - cub->pos_x + (1 - cub->step_x) / 2) / cub->raydir_x;
		else
			cub->wall_dist = (cub->map_y - cub->pos_y + (1 - cub->step_y) / 2) / cub->raydir_y;
		cub->line_height = (int)(cub->res_y / cub->wall_dist);
		cub->draw_start = -cub->line_height / 2 + cub->res_y / 2;
		if(cub->draw_start < 0)
			cub->draw_start = 0;
		cub->draw_end = cub->line_height / 2 + cub->res_y / 2;
		if(cub->draw_end >= cub->res_y)
			cub->draw_end = cub->res_y - 1;
		y = cub->draw_start;
		if (cub->side == 0)
			color = 0x318E29;
		else if (cub->side == 1)
			color = 0x31C724;
		while (y < cub->draw_end)
		{
			if (x < cub->res_x && y < cub->res_y)
			ft_memcpy(cub->img_ptr + 4 * cub->res_x * y + x * 4, &color, sizeof(int));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->image, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->image);
}

void	move(t_cub3d *cub)
{
	if (cub->up == 1)
	{
		if (worldMap[(int)(cub->pos_x + cub->dir_x * cub->move_speed)][(int)(cub->pos_y)] == 0)
			cub->pos_x += cub->dir_x * cub->move_speed;
		if (worldMap[(int)(cub->pos_x)][(int)(cub->pos_y + cub->dir_y * cub->move_speed)] == 0)
			cub->pos_y += cub->dir_y * cub->move_speed;
	}
	if (cub->down == 1)
	{
		if (worldMap[(int)(cub->pos_x - cub->dir_x * cub->move_speed)][(int)(cub->pos_y)] == 0)
			cub->pos_x -= cub->dir_x * cub->move_speed;
		if (worldMap[(int)(cub->pos_x)][(int)(cub->pos_y - cub->dir_y * cub->move_speed)] == 0)
			cub->pos_y -= cub->dir_y * cub->move_speed;
	}
}

void	turn(t_cub3d *cub)
{
	if (cub->left == 1)
    {
		cub->olddir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(cub->rot_speed) - cub->dir_y * sin(cub->rot_speed);
		cub->dir_y = cub->olddir_x * sin(cub->rot_speed) + cub->dir_y * cos(cub->rot_speed);
		cub->oldplane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(cub->rot_speed) - cub->plane_y * sin(cub->rot_speed);
		cub->plane_y = cub->oldplane_x * sin(cub->rot_speed) + cub->plane_y * cos(cub->rot_speed);
    }
	if (cub->right == 1)
    {
		cub->olddir_x = cub->dir_x;
		cub->dir_x = cub->dir_x * cos(-cub->rot_speed) - cub->dir_y * sin(-cub->rot_speed);
		cub->dir_y = cub->olddir_x * sin(-cub->rot_speed) + cub->dir_y * cos(-cub->rot_speed);
		cub->oldplane_x = cub->plane_x;
		cub->plane_x = cub->plane_x * cos(-cub->rot_speed) - cub->plane_y * sin(-cub->rot_speed);
		cub->plane_y = cub->oldplane_x * sin(-cub->rot_speed) + cub->plane_y * cos(-cub->rot_speed);
    }
}

int		motion(t_cub3d *cub)
{
	move(cub);
	turn(cub);
	raycasting(cub);
	return (0);
}

int	main()
{
	t_cub3d cub;
	int fd;
	
	fd = open("desc.cub", O_RDONLY);
	read_desc(fd, &cub);
	
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.res_x, cub.res_y, "cub3d");

	mlx_hook(cub.win_ptr, 17, 0L, exit_prog, &cub);	/* termine le programme quand on ferme la fenetre */
	mlx_hook(cub.win_ptr, 2, (1L<<0), press_key, &cub);
	mlx_hook(cub.win_ptr, 3, (1L<<1), real_key, &cub);
	init_cub(&cub);
	raycasting(&cub);
	mlx_loop_hook(cub.mlx_ptr, motion, &cub);
	mlx_loop(cub.mlx_ptr);
}
