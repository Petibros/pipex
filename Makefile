NAME = pipex

C_MANDA = mandatory/free_and_exit.c mandatory/parsing.c mandatory/pipex.c

C_LIBFT = libft/ft_split.c libft/ft_strjoin.c libft/ft_strdup.c \
            libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strchr.c

C_BONUS = bonus/free_and_exit_bonus.c bonus/parsing_bonus.c bonus/pipex_bonus.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

O_MANDA = $(C_MANDA:.c=.o)

O_LIBFT = $(C_LIBFT:.c=.o)

O_BONUS = $(C_BONUS:.c=.o)

CFLAGS += -Wall -Wextra -Werror -g

all : $(NAME)

$(NAME) : $(O_MANDA) $(O_LIBFT)
		cc $(CFLAGS) $(O_MANDA) $(O_LIBFT) -o $(NAME)

bonus : fclean $(O_BONUS) $(O_LIBFT)
		cc $(CFLAGS) $(O_BONUS) $(O_LIBFT) -o $(NAME)

clean :
		rm -f $(O_MANDA) $(O_LIBFT) $(O_BONUS)

fclean : clean
		rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
