# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 14:24:43 by zamgar            #+#    #+#              #
#    Updated: 2024/11/18 21:19:32 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_PATH = ./libft/

LIBFT_NAME = libft.a

LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

SRC = src/main.c src/env.c src/exec.c src/pipex.c src/export.c src/unset.c src/tokens.c src/tokens_utils.c src/echo.c src/cmd_redirect.c

OBJS := $(SRC:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -I ./includes

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	make -sC $(LIBFT_PATH)

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -o $(NAME)

clean:
	make clean -sC $(LIBFT_PATH)
	rm -rf $(OBJS)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re