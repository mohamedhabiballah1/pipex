# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 14:33:08 by mhabib-a          #+#    #+#              #
#    Updated: 2023/01/08 17:23:56 by mhabib-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = pipex.c pipex_utils.c pipex_utils1.c pipex_pid.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIB = pipex.h

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

%.o : %.c $(LIB)
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all