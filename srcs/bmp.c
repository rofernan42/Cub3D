/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:36:46 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/10 11:37:55 by rofernan         ###   ########.fr       */
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

	int red[cub->res_x][cub->res_y];
	int green[cub->res_x][cub->res_y];
	int blue[cub->res_x][cub->res_y];
	for(int i=0; i<cub->res_x; i++)
	{
		for(int j=0; j<cub->res_y; j++)
		{
			int x=i; int y=(cub->res_y-1)-j;
			int r = red[i][j]*255;
			int g = green[i][j]*255;
			int b = blue[i][j]*255;
			if (r > 255) r=255;
			if (g > 255) g=255;
			if (b > 255) b=255;
			img[(x+y*cub->res_x)*3+2] = (unsigned char)(r);
			img[(x+y*cub->res_x)*3+1] = (unsigned char)(g);
			img[(x+y*cub->res_x)*3+0] = (unsigned char)(b);
		}
	}


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
	// write(fd, &pix, 1);
	// fwrite(bmpfileheader,1,14,fd);
	// fwrite(bmpinfoheader,1,40,fd);
	// for(int i=0; i<cub->res_y; i++)
	// {
 	//    fwrite(img+(cub->res_x*(cub->res_y-i-1)*3),3,cub->res_x,fd);
 	//    fwrite(bmppad,1,(4-(cub->res_x*3)%4)%4,fd);
	// }
	printf("test1");
	free(img);
	close(fd);
}


// if (ft_strcmp(arg, "--save") == 0)
// 	{
		
// 	}
// 	exit_prog();