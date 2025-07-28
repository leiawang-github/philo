# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leia <leia@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 16:19:48 by leia              #+#    #+#              #
#    Updated: 2025/07/27 10:05:33 by leia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c monitor_func.c parse_args.c routine.c sleep.c utilities.c \
      init_funcs.c cleanup_funcs.c death_check.c action_funcs.c

OBJ = $(SRC:.c=.o)

CC = cc  

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re