CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC =heredoc.c pipex_bonus.c ./m/get_next_line_bonus.c ./m/get_next_line_utils_bonus.c 
NAME  = here_doc
RM = rm -f

all: ${NAME} 

${NAME}: ${SRC}
	make -C ../ft_printf/
	make -C ../ft_fprintf/
	make -C ../libft/
	${CC} ${SRC} ../libft/libft.a ../ft_printf/libftprintf.a ../ft_fprintf/libftfprintf.a -o $(NAME)

clean:
	make -C ../libft/ clean
	make -C ../ft_fprintf/ clean
	make -C ../ft_printf/ clean

fclean: clean
	${RM} $(NAME)
	make -C ../libft/ fclean
	make -C ../ft_fprintf/ fclean
	make -C ../ft_printf/ fclean

re: fclean all