/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:08:32 by rofernan          #+#    #+#             */
/*   Updated: 2019/12/04 14:02:00 by rofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Libft/libft.h"

/*
** http://projet-moteur-3d.e-monsite.com/pages/raycasting/raycasting.html
** https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html
** https://user.oc-static.com/ftp/mateo21/sdlkeysym.html
**
** IMPORTANT: Event et EventMask: https://code.woboq.org/qt5/include/X11/X.h.html

** tuto raycasting: https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
** code C tuto: http://zupi.free.fr/PTuto/index.php?ch=ptuto&p=s3De
** https://lodev.org/cgtutor/raycasting.html
*/

/* Fonctions externes autorisées:
** -open, read, write, malloc, free, perror,
** strerror, exit
** -Toutes les fonctions de la lib math (-lm
** man man 3 math)
** -Toutes les fonctions de la MinilibX
*/

typedef struct	s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			res_x;
	int			res_y;
	void		*image;
}				t_win;

typedef struct	s_img
{
	void		*image;
	void		*img_ptr;
	int			x;
	int			y;
	int			bpp;
	int			endian;
	int			sl;
}				t_img;

typedef struct	s_cub3d
{
	char		**map;
	double		posX; //position de depart
	double		posY; //position de depart
	double		dirX; //vecteur en X
	double		dirY; //vecteur en Y
	double		time; //temps sequence courante
	double		oldtime; //temps image precedente

}				t_cub3d;


/*typedef struct	s_tex
{
	int			;
	int			res_y;
}				t_tex;
*/
#endif
