# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 08:53:07 by bgazur            #+#    #+#              #
#    Updated: 2025/07/17 11:18:29 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

CC =			cc
CFLAGS =		-Wall -Werror -Wextra
RM =			rm -rf

DIR_HDR  =		include
DIR_OBJ  =		objects
DIR_SRC  =		src
DIR_LIBFT =		lib/libft

HDR =			$(DIR_HDR)/minishell.h
HDR_LIBFT =		$(DIR_LIBFT)/$(DIR_HDR)/libft.h
OBJ =			$(SRC:%.c=$(DIR_OBJ)/%.o)
SRC =			main.c \

LIBFT =			$(DIR_LIBFT)/libft.a
LIBFT_FLAGS =	-L$(DIR_LIBFT) -lft


all: $(DIR_OBJ) $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_FLAGS)
	@echo "✅ Build $(GREEN)$(NAME) $(NC)successfully! 🎉"

$(LIBFT): $(HDR_LIBFT)
	@$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)
	@echo "📁 Creating directory for $(NAME) objects"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HDR)
	@$(CC) $(CFLAGS) -I$(DIR_HDR) -I$(DIR_LIBFT)/include -c $< -o $@
	@echo "... 🛠️ compiling $<"

clean:
	@$(RM) $(DIR_OBJ)
	@$(MAKE) -C $(DIR_LIBFT) clean
	@echo "🧹 Objects of $(NAME) are removed! -> 🗑️"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(DIR_LIBFT) fclean
	@echo "🧹 Executable $(NAME) is removed! -> 🗑️ "

re: fclean all

.PHONY: all clean fclean re
