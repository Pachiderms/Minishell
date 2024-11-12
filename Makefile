NAME = minishell

INCLUDES = includes/
LIBFT_DIR = libft/
LIBFT = ${LIBFT_DIR}libft.a
SRC_DIR = src/
SRC = main.c token.c\

OBJS = ${addprefix ${SRC_DIR}, ${SRC:.c=.o}}
DEPS = ${addprefix ${SRC_DIR},${SRC:.c=.d}}

CC = clang

CFLAGS = -lreadline -Wall -Wextra -Werror

.c.o:
	${CC} ${C_FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	make -C ${LIBFT_DIR}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -I ${INCLUDES} -o ${NAME}

clean:
	make clean -C ${LIBFT_DIR}
	rm -f ${DEPS} ${OBJS}

fclean: clean
	make fclean -C ${LIBFT_DIR}
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include ${DEPS}
