# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 14:24:43 by zamgar            #+#    #+#              #
#    Updated: 2025/02/04 02:23:11 by tzizi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

GREEN	= \033[0;32m
RED		= \033[0;31m
RESET	= \033[0m

LIBFT_PATH = ./libft/

LIBFT_NAME = libft.a

LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

SRC = src/exec/exec42.c src/parsing/split_kqs_utils.c src/parsing/parsing_utils2.c src/init_main.c src/utils/free2.c src/utils/mega_utils.c src/parsing/check2.c src/exec/exec2_utils.c src/builtins/echo_utils.c src/parsing/split_kqs.c src/parsing/check.c src/parsing/t_cmd_utils.c src/main.c src/builtins/env.c src/exec/exec.c src/exec/exec2.c src/builtins/export.c src/builtins/export1.c src/builtins/export+=.c src/builtins/unset.c src/builtins/unset1.c src/parsing/tokens_utils.c src/parsing/tokens_utils1.c src/parsing/parsing_utils.c src/parsing/parsing_utils1.c src/builtins/echo.c src/builtins/cd.c src/builtins/cd1.c src/builtins/pwd.c src/exec/cmd_redirect.c src/utils/free.c src/utils/signals.c src/heredoc.c

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