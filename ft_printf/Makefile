SRCS =  ft_helpers.c ft_printf.c 
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

all : ${NAME}
       
${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
	rm -f ${OBJS} 

fclean: clean
	rm -f ${NAME} 

re: fclean all

.SECONDARY: ${OBJS} 