# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leia <leia@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 16:19:48 by leia              #+#    #+#              #
#    Updated: 2025/07/28 12:33:41 by leia             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c monitor_func.c parse_args.c routine.c sleep.c utilities.c \
      init_funcs.c cleanup_funcs.c action_funcs.c

OBJ = $(SRC:.c=.o)

CC = cc  -g

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

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