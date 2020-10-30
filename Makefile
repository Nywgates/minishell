# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 15:19:20 by laballea          #+#    #+#              #
#    Updated: 2020/10/30 15:07:33 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

FT = ./error_main_bis.c ./ft_exit.c ./get_env_utils2.c ./error_main.c ./get_next_line2.c ./quote3.c ./quote4.c ./echo.c ./export.c ./export2.c ./ft_argument.c ./ft_atoi.c ./ft_exec_pipe.c ./ft_exec_pipe2.c ./ft_exec_pipe3.c ./ft_filter.c ./ft_isalpha.c ./ft_isdigit.c ./ft_itoa.c ./ft_list_utils.c ./ft_path.c ./ft_pid_utils.c ./ft_putstr_fd.c ./ft_set_split.c ./ft_set_split_help.c ./ft_split.c ./ft_split_count.c ./ft_strncmp.c ./ft_swap.c ./gest_fd.c ./gest_fd2.c ./get_env.c ./get_env_utils.c ./get_next_line.c ./get_next_line_utils.c ./main.c quote1.c ./quote2.c ./sig.c ./unset.c ./utils.c ./utils2.c ./utils4cd.c ./utils4cdget.c

FO = ${FT:.c=.o}

INCLUDE = ./minishell.h

NAMA	= minishell.a

NAME	= minishell

LINK	= ar rc

$(NAME):	${FO} ${FT} ${INCLUDE}
			${LINK} ${NAMA} ${FO}
			${CC} ${CFLAGS} ${NAMA} -o ${NAME}
			rm minishell.a

all: ${NAME}

clean:
	rm -rf ${FO}

fclean: clean
		rm -rf ${NAME}

re: fclean all

.PHONY : all clean fclean re
