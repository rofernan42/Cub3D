# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 15:44:33 by rofernan          #+#    #+#              #
#    Updated: 2020/02/07 15:08:34 by rofernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				=	cub3D

SRCS_PATH			=	./srcs
INC_PATH			=	./includes

SRCS_NAME			=	actions.c			\
						arrange_map.c		\
						bmp.c				\
						check_content.c		\
						check_map.c			\
						colors.c			\
						create_map.c		\
						draw_ceil_floor.c	\
						draw_walls.c		\
						draw.c				\
						error.c				\
						exit.c				\
						free.c				\
						hud.c				\
						image.c				\
						init_desc.c			\
						init_var.c			\
						main.c				\
						motion.c			\
						pix.c				\
						raycasting.c		\
						resolution.c		\
						sprite_sorting.c	\
						sprite.c			\
						textures.c			\

INC_NAME			=	cub3d.h

SRCS				=	$(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
INC					=	$(addprefix $(INC_PATH)/, $(INC_NAME))

CC					=	gcc

CFLAGS				=	-Wall -Wextra -Werror -I./
MLX					=	-lmlx -framework OpenGL -framework AppKit
LIB					=	./libft/libft.a

all:					$(NAME)

$(NAME):				
						@(make -C ./libft/)
						@($(CC) $(CFLAGS) $(MLX) $(LIB) $(SRCS) -o $(NAME))
						@(echo "\033[32m=== COMPILATION CUB3D OK ===\033[0m")

clean:
						@(make clean -C ./libft/)

fclean:
						@(rm -rf $(NAME))
						@echo "\033[34m=== REPERTORY CUB3D CLEANED ===\033[0m"
						@(make fclean -C ./libft/)

re:						fclean all

.PHONY:					clean fclean re all bonus
