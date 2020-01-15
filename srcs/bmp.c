/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:36:46 by rofernan          #+#    #+#             */
/*   Updated: 2020/01/15 11:27:41 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_header(unsigned char *header, int param)
{
	header[0] = (unsigned char)(param);
	header[1] = (unsigned char)(param >> 8);
	header[2] = (unsigned char)(param >> 16);
	header[3] = (unsigned char)(param >> 24);
}

static void	init_header(t_cub3d *cub, t_bmp *bmp)
{
	int i;

	i = 0;
	while (i < 14)
		bmp->fileheader[i++] = 0;
	bmp->fileheader[0] = 'B';
	bmp->fileheader[1] = 'M';
	bmp->fileheader[10] = 54;
	i = 0;
	while (i < 40)
		bmp->infoheader[i++] = 0;
	bmp->infoheader[0] = 40;
	bmp->infoheader[12] = 1;
	bmp->infoheader[14] = 24;
	i = 0;
	while (i < 3)
		bmp->pad[i++] = 0;
	set_header(&bmp->fileheader[2], bmp->filesize);
	set_header(&bmp->infoheader[4], cub->res_x);
	set_header(&bmp->infoheader[8], cub->res_y);
	write(bmp->fd, bmp->fileheader, 14);
	write(bmp->fd, bmp->infoheader, 40);
}

static void	get_color_bmp(t_cub3d *cub, t_bmp *bmp, int j)
{
	int i;
	int x;
	int y;

	i = 0;
	while (i < cub->res_x)
	{
		x = i;
		y = cub->res_y - 1 - j;
		bmp->color = \
			*(int*)(cub->img_ptr + (cub->res_x * y + x) * cub->bit_pix / 8);
		write(bmp->fd, &bmp->color, 3);
		i++;
	}
}

static void	draw_bmp(t_cub3d *cub, t_bmp *bmp)
{
	int i;
	int j;

	j = 0;
	while (j < cub->res_y)
	{
		get_color_bmp(cub, bmp, j);
		i = 0;
		while (i < (4 - (cub->res_x * 3) % 4) % 4)
		{
			write(bmp->fd, &bmp->pad, 1);
			i++;
		}
		j++;
	}
}

void		convert_bmp(t_cub3d *cub)
{
	t_bmp	bmp;

	bmp.filesize = 54 + 3 * cub->res_x * cub->res_y;
	bmp.img = malloc((sizeof(char) * 3 * cub->res_x * cub->res_y));
	ft_memset(bmp.img, 0, 3 * cub->res_x * cub->res_y);
	bmp.fd = open("img.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	init_header(cub, &bmp);
	draw_bmp(cub, &bmp);
	free(bmp.img);
	close(bmp.fd);
}
