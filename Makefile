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

GREEN	= \033[0;32m
RED		= \033[0;31m
RESET	= \033[0m

LIBFT_PATH = ./libft/

LIBFT_NAME = libft.a

LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

SRC = src/main.c src/env.c src/exec.c src/pipex.c src/export.c src/unset.c src/tokens.c src/tokens_utils.c src/echo.c src/cd.c src/pwd.c src/cmd_redirect.c src/utils.c src/free.c src/prep_pipex.c src/signals.c src/get_next_line.c src/heredoc.c

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
	mv src/*.o objs
	@echo "$(NAME): $(GREEN)$(NAME) compiled.$(RESET)"
	@echo ".o files in directory 'objs'"

clean:
	make clean -sC $(LIBFT_PATH)
	rm -rf objs

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re