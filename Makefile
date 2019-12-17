# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 15:44:33 by rofernan          #+#    #+#              #
#    Updated: 2019/12/06 19:26:21 by rofernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				=	cub3d

LIB_PATH			=	./libft
SRCS_PATH			=	./srcs
INC_PATH			=	./includes
OBJS_PATH			=	./objs

SRCS_NAME			=	drawing.c		\
						init_var.c		\
						motion.c		\
						raycasting.c	\
						main.c			\

INC_NAME			=	cub3d.h

OBJS_NAME			=	$(SRCS_NAME:.c=.o)

LIB					=	$(addprefix $(LIB_PATH)/, $(LIB_NAME))
SRCS				=	$(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
INC					=	$(addprefix $(INC_PATH)/, $(INC_NAME))
OBJS				=	$(addprefix $(OBJS_PATH)/, $(OBJS_NAME))
OBJSLIB				=	$(addprefix $(OBJS_PATH)/, $(OBJSLIB_NAME))

CC					=	gcc

CFLAGS				=	-Wall -Wextra -Werror -I./includes
MLX					=	-I./ -lmlx -framework OpenGL -framework AppKit

all:					$(NAME)

$(NAME):				$(OBJS) $(OBJSLIB)
						$(CC) $(CFLAGS) $(MLX) $^ -o $@

$(OBJS_PATH)/%.o:		$(SRCS_PATH)/%.c $(LIB_PATH)/%.c
						@mkdir $(OBJS_PATH) 2> /dev/null || true
						@$(CC) -o $@ -c $<

clean:
						rm -rf $(OBJS) $(OBJSLIB)

fclean:					clean
						rm -rf ./objs $(NAME)

re:						fclean all

.PHONY:					clean fclean re all bonus
