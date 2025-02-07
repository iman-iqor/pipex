CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ./mandatory_src/pipex.c ./mandatory_src/utils1.c ./mandatory_src/utils2.c 
BSRC = ./bonus_src/heredoc.c ./bonus_src/pipex_bonus.c ./bonus_src/m/get_next_line_bonus.c ./bonus_src/m/get_next_line_utils_bonus.c 
NAME  = pipex
RM = rm -f

all: ${NAME} 

${NAME}: ${SRC}
	make -C ./ft_printf/
	make -C ./ft_fprintf/
	make -C ./libft/
	${CC} ${SRC} ./libft/libft.a ./ft_printf/libftprintf.a ./ft_fprintf/libftfprintf.a -o $(NAME)
bonus:
	make -C ./ft_printf/
	make -C ./ft_fprintf/
	make -C ./libft/
	${CC} ${BSRC} ./libft/libft.a ./ft_printf/libftprintf.a ./ft_fprintf/libftfprintf.a -o $(NAME)

clean:
	make -C ./libft/ clean
	make -C ./ft_fprintf/ clean
	make -C ./ft_printf/ clean

fclean: clean
	${RM} $(NAME)
	make -C ./libft/ fclean
	make -C ./ft_fprintf/ fclean
	make -C ./ft_printf/ fclean

re: fclean all