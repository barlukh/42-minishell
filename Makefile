# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/14 09:44:15 by bgazur            #+#    #+#              #
#    Updated: 2025/07/14 09:44:53 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell
CC =		cc
CFLAGS =	-Wall -Werror -Wextra
RM =		rm -f

INC_DIR =	include
OBJ_DIR =	objects
SRC_DIR =	src

HDR =		$(INC_DIR)/minishell.h

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)

SRC =		main.c

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ_DIR) $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
