NAME	= pipex

SRCS 	= srcs/pipex.c srcs/pipex_utils.c
OBJS 	= ${SRCS:.c=.o}
MAIN	= srcs/pipex.c

HEADER	= -Iincludes

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g
RM		= rm -f

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all: 		${NAME}

${NAME}:	${OBJS}
					@make re -C ./libft
					@$(CC) ${OBJS} -Llibft -lft -o ${NAME}

clean:
					@make clean -C ./libft
					@${RM} ${OBJS}

fclean: 	clean
					@make fclean -C ./libft
					@${RM} $(NAME)
					@${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re