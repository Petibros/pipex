# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 00:51:36 by sacgarci          #+#    #+#              #
#    Updated: 2025/01/07 15:55:55 by sacgarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

C_LIBFT = libft/ft_split.c libft/ft_strjoin.c libft/ft_strdup.c \
            libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strchr.c \
			libft/free_char_array.c

C_FILES = src_files/free_and_exit.c src_files/parsing.c src_files/pipex.c \
			get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
			src_files/child_proc.c src_files/find_proc.c

O_FILES = $(C_FILES:.c=.o)

O_LIBFT = $(C_LIBFT:.c=.o)

CFLAGS += -Wall -Wextra -Werror -g

all : $(NAME)

$(NAME) : $(O_FILES) $(O_LIBFT)
		cc $(CFLAGS) $(O_FILES) $(O_LIBFT) -o $(NAME)

clean :
		rm -f $(O_MANDA) $(O_LIBFT) $(O_FILES)

fclean : clean
		rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
