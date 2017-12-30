# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdjeghba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 13:30:08 by sdjeghba          #+#    #+#              #
#    Updated: 2017/12/30 05:33:08 by sdjeghba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf
INC			=	-I./includes
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
LIB			=	./libft/libft.a
P_LIB		=	./libft/
P_SRC		=	./srcs/
MLXFLAGS	=	-L/usr/local/lib/ -lmlx -framework OpenGL -framework Appkit

SRCS		=	$(P_SRC)main.c				\
				$(P_SRC)fdf.c				\
				$(P_SRC)tools.c				\
				$(P_SRC)get_map.c

OBJS		=	$(SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				make -C $(P_LIB)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC) $(MLXFLAGS) $(LIB)

%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $@

RM			=	rm -rf

clean:
				make -C $(P_LIB) clean
				$(RM) $(OBJS)

fclean:			clean
				make -C $(P_LIB) fclean
				$(RM) $(NAME)

re:				fclean all
