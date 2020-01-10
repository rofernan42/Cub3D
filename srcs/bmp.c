/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:36:46 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/10 19:36:59 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	convert_bmp(t_cub3d *cub)
{
	char	*img;
	int		filesize;
	int		fd;

	filesize = 54 + 3 * cub->res_x * cub->res_y;
	img = malloc((sizeof(char) * 3 * cub->res_x * cub->res_y));
	ft_memset(img, 0, 3 * cub->res_x * cub->res_y);

	


	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(cub->res_x);
	bmpinfoheader[ 5] = (unsigned char)(cub->res_x>> 8);
	bmpinfoheader[ 6] = (unsigned char)(cub->res_x>>16);
	bmpinfoheader[ 7] = (unsigned char)(cub->res_x>>24);
	bmpinfoheader[ 8] = (unsigned char)(cub->res_y);
	bmpinfoheader[ 9] = (unsigned char)(cub->res_y>> 8);
	bmpinfoheader[10] = (unsigned char)(cub->res_y>>16);
	bmpinfoheader[11] = (unsigned char)(cub->res_y>>24);

	fd = open("img.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND);
	int i = 0;
	int j;
	while (i < 14)
		write(fd, &bmpfileheader[i++], 1);
	i = 0;
	while (i < 40)
		write(fd, &bmpinfoheader[i++], 1);
	i = 0;
	
	int col_img;
	int color;
	int x;
	int y;
	while (j < cub->res_y)
	{
		i = 0;
		while (i < cub->res_x)
		{
			x = i;
			y = cub->res_y - 1 - j;
			col_img = *(int*)(cub->img_ptr + (cub->res_x * y + x) * cub->bit_pix / 8);
			color = (col_img & 0xFF0000) | (col_img & 0x00FF00) | (col_img & 0x0000FF);
			write(fd, &color, 3);
			i++;
		}
		i = 0;
		while (i < (4 - (cub->res_x * 3) % 4) % 4)
		{
			write(fd, &bmppad, 1);
			i++;
		}
		j++;
	}
	printf("test1");
	free(img);
	close(fd);
}
