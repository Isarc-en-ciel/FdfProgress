# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 12:27:30 by iwaslet           #+#    #+#              #
#    Updated: 2024/01/25 16:38:33 by iwaslet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS = fdf_src.c \
		fdf_utils.c \
		fdf_map_management.c \
		get_next_line.c \
		get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

%.o: %.c
	$(CC) $(CFLAGS) -include Libft/libft.h -include minilibx/mlx.h -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./minilibx
	make -C ./Libft
	$(CC) $(OBJS) $(CFLAGS) ./libft/libft.a -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C ./minilibx
	make clean -C ./Libft

fclean: clean
	rm -rf $(NAME)
	make clean -C ./minilibx
	make fclean -C ./Libft

re: fclean all

.PHONY: all re clean fclean
