# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 14:24:43 by zamgar            #+#    #+#              #
#    Updated: 2025/01/27 13:38:22 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

GREEN	= \033[0;32m
RED		= \033[0;31m
RESET	= \033[0m

LIBFT_PATH = ./libft/

LIBFT_NAME = libft.a

LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

SRC = src/main.c src/builtins/env.c src/exec/exec.c src/exec/exec2.c src/builtins/export.c src/builtins/export1.c src/builtins/export+=.c src/builtins/unset.c src/builtins/unset1.c src/parsing/tokens.c src/parsing/tokens_utils.c src/parsing/tokens_utils1.c src/builtins/echo.c src/builtins/cd.c src/builtins/cd1.c src/builtins/pwd.c src/exec/cmd_redirect.c src/parsing/parsing_utils.c src/parsing/parsing_utils1.c src/utils/free.c src/exec/exec0.c src/utils/signals.c src/utils/get_next_line.c src/heredoc.c

OBJS := $(SRC:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -gdwarf-4 -I ./includes

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	make -sC $(LIBFT_PATH)

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) compiled.$(RESET)"

valgrind:
	valgrind --leak-check=full ./minishell

clean:
	make clean -sC $(LIBFT_PATH)
	find . -type f -name '*.o' -delete

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

nothing: all clean
	clear

re: fclean all

.PHONY: all valgrind clean fclean nothing re