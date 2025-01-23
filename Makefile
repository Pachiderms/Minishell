# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 14:24:43 by zamgar            #+#    #+#              #
#    Updated: 2025/01/23 13:40:23 by tzizi            ###   ########.fr        #
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

CC = clang #gcc?
FLAGS = -Wall -Wextra -Werror -gdwarf-4 -I ./includes

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	make -sC $(LIBFT_PATH)

$(NAME): $(LIBFT_LIB) $(OBJS)
	mkdir -p objs
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -o $(NAME)
	mv src/*.o src/builtins/*.o src/parsing/*.o src/exec/*.o src/utils/*.o objs
	@echo "$(NAME): $(GREEN)$(NAME) compiled.$(RESET)"
	@echo ".o files in directory 'objs'"

valgrind:
	valgrind --leak-check=full ./minishell

clean:
	make clean -sC $(LIBFT_PATH)
	rm -rf objs

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all valgrind clean fclean re