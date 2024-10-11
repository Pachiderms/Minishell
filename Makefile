NAME = minishell_test

LIBFT_DIR = libft/
LIBFT = ${LIBFT_DIR}libft.a
SRC = main.c \

OBJS = ${SRC:.c=.o}
DEPS = ${SRC:.c=.d}

CC = gcc

CFLAGS = -lreadline -Wall -Wextra -Werror

.c.o:
	${CC} ${C_FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	make -C ${LIBFT_DIR}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

clean:
	make clean -C ${LIBFT_DIR}
	rm -f ${DEPS} ${OBJS}

fclean: clean
	make fclean -C ${LIBFT_DIR}
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include ${DEPS}
