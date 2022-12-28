# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 14:33:08 by mhabib-a          #+#    #+#              #
#    Updated: 2022/12/27 15:46:08 by mhabib-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = pipex.c pipex_utils.c 
OBJ = $(SRC:.c=.o)
CC = cc
#CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIB = pipex.h

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(SRC) -o $(NAME)

%.o : %.c $(LIB)
	$(CC) $(SRC) -c $<

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
	
re : fclean all