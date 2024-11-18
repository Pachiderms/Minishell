# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzizi <tzizi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 14:24:43 by zamgar            #+#    #+#              #
#    Updated: 2024/11/18 15:41:46 by tzizi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_atoi.c \
	ft_isspace.c \
	ft_split.c \
	ft_strjoin.c \
	ft_strdup.c \
	ft_strncmp.c \
	ft_strcmp.c \
	ft_strchr.c \
	ft_substr.c \
	ft_strlen.c

BFILES =	ft_atoi.o \
		ft_isspace.o \
		ft_split.o \
		ft_strjoin.o \
		ft_strdup.o \
		ft_strncmp.o \
		ft_strchr.o \
		ft_substr.o \
		ft_strlen.o

OBJS = ${SRC:.c=.o}

NAME = libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror -I ./includes

.c.o:
	$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
