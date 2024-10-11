LIBC = ft_isdigit.c ft_strlen.c \
	ft_bzero.c ft_strncmp.c ft_atoi.c \
	ft_calloc.c ft_strdup.c	ft_substr.c \

ADD = ft_strjoin.c \
	ft_split.c ft_itoa.c \
	ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	

SRCS = ${LIBC}${ADD}

OBJS = ${SRCS:.c=.o}
DEPS = ${SRCS:.c=.d}

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -I ./

.c.o:
	${CC} $(CFLAGS) -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	ar -rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	/bin/rm -f ${DEPS} ${OBJS}

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include ${DEPS}
