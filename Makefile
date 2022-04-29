# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmichel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 13:17:34 by lmichel           #+#    #+#              #
#    Updated: 2021/11/21 13:52:45 by lmichel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

SRCS	= pipex_utils.c pipex.c pip_utils.c ft_split.c

OBJS	= $(SRCS:.c=.o)

HEADER	= pipex.h

CFLAGS	= -Wall -Wextra -Werror -I $(HEADER)

CC		= gcc

.PHONY: all clean fclean re

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all