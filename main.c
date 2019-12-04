/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:38:22 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/04 15:02:33 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ABS(x) (x < 0) ? -x : x

int		exit_prog(void)
{
	exit(1);
	return (0);
}

int	read_desc(int fd, t_win *win)
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
			win->res_x = ft_atoi(&line[1]);
			while (line[i] && line[i] == ' ')
				i++;
			while (line[i] && (line[i] >= '0' && line[i] <= '9'))
				i++;
			win->res_y = ft_atoi(&line[i]);
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

int deal_key(int key, t_win *win)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (key == 0)
	{
	while (i < 300)
	{
		j = 0;
		while (j < 200)
		{
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, j, 0x32cd32);
			j++;
		}
		i++;
	}
	}
	return (0);
}

int real_key(int key, t_win *win)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (key == 0)
	{
	while (i < 300)
	{
		j = 0;
		while (j < 200)
		{
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, i, j, 0x000000);
			j++;
		}
		i++;
	}
	}
	return (0);
}

void	draw_wall()
{
	
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



int	main()
{
	t_win win;
	t_img img;
	int fd;
	
	fd = open("desc.cub", O_RDONLY);
	read_desc(fd, &win);
	
	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, win.res_x, win.res_y, "cub3d");
	img.image = mlx_new_image(win.mlx_ptr, win.res_x, win.res_y);
	img.img_ptr = mlx_get_data_addr(img.image, &img.bpp, &img.sl, &img.endian);

	mlx_hook(win.win_ptr, 17, 0L, exit_prog, &win);	/* termine le programme quand on ferme la fenetre */
	// mlx_hook(win.win_ptr, 2, (1L<<0), deal_key, &win); /* affiche le carre de couleur quand on appuie sur 'a' */
	// mlx_hook(win.win_ptr, 3, (1L<<1), real_key, &win); /* enleve le carre de couleur quand on relache 'a' */
	int posX = 6, posY = 3;  //x and y start position
	double dirX = 0, dirY = 1; //initial direction vector
	double planeX = 0.66, planeY = 0; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	double cameraX; //x-coordinate in camera space
    double rayDirX;
    double rayDirY;
	int x;
	x = 0;
	int mapX;
	int mapY;

//length of ray from current position to next x or y-side
	double sideDistX;
    double sideDistY;

	//length of ray from one x or y-side to next x or y-side
      double deltaDistX;
      double deltaDistY;
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

	int lineHeight;
	int drawStart;
    int drawEnd;

	int y;

	while (x < win.res_x)
    {
      //calculate ray position and direction
      cameraX = (double)(2 * x / (double)win.res_x) - 1; //x-coordinate in camera space
      rayDirX = dirX + planeX * cameraX;
      rayDirY = dirY + planeY * cameraX;

	  //which box of the map we're in
      mapX = posX;
      mapY = posY;

    //length of ray from one x or y-side to next x or y-side
    	deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

	  if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }

	hit = 0;
	//perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
      }

	  if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;


	//Calculate height of line to draw on screen
      lineHeight = (int)(win.res_y / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      drawStart = -lineHeight / 2 + win.res_y / 2;
      if(drawStart < 0)
	  	drawStart = 0;
      drawEnd = lineHeight / 2 + win.res_y / 2;
      if(drawEnd >= win.res_y)
	  	drawEnd = win.res_y - 1;
	y = drawStart;
	int color;
	if (side == 0)
		color = 0x32cd32;
	else if (side == 1)
		color = 0xFFFFFF;
	while (y < drawEnd)
	{
		if (x < win.res_x && y < win.res_y)
			ft_memcpy(img.img_ptr + 4 * win.res_x * y + x * 4,
				&color, sizeof(int));
			y++;
	}
	// while (y <= drawEnd)
	// {
	//   mlx_pixel_put(win.mlx_ptr, win.win_ptr, x, y, color);
	//   y++;
	// }
	x++;
	}
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, img.image, 0, 0);
	// mlx_destroy_image(win.mlx_ptr, img.image);
	mlx_loop(win.mlx_ptr);
}
