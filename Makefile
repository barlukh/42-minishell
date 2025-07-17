# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 08:53:07 by bgazur            #+#    #+#              #
#    Updated: 2025/07/17 08:56:56 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

DIR_SRC =		src
DIR_OBJ =		objects
DIR_LIBFT =		lib/libft
DIR_LIBFT_INC =	$(DIR_LIBFT)/include

COMPILER =		cc
CFLAGS =		-Wall -Wextra -Werror
HEADERS =		-Iinclude -I$(DIR_LIBFT_INC)
LIBFT_FLAGS =	-L$(DIR_LIBFT) -lft
RM =			rm -rf

MAIN_SRC =		main.c \

SRC = $(addprefix $(DIR_SRC)/, $(MAIN_SRC))

OBJECTS = $(SRC:%.c=$(DIR_OBJ)/%.o)

LIBFT = $(DIR_LIBFT)/libft.a

GREEN = \033[0;32m
NC = \033[0m

all:  $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(DIR_LIBFT)

$(NAME): $(LIBFT) $(OBJECTS) 
	@$(COMPILER) $(CFLAGS) $(OBJECTS) -o $@ $(LIBFT_FLAGS)
	@echo "✅ Build $(GREEN)$(NAME)$(NC) successfully! 🎉"


$(DIR_OBJ)/%.o: %.c | $(DIR_OBJ)
	@mkdir -p $(dir $@)
	@$(COMPILER) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "... 🛠️ compiling $<"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

clean:
	@$(RM) $(DIR_OBJ)
	@make --no-print-directory clean -C $(DIR_LIBFT)
	@echo "🧹 Cleaned object files."

fclean: clean
	@$(RM) $(NAME)
	@make --no-print-directory fclean -C $(DIR_LIBFT)
	@echo "🧹 Removed executables."

re: fclean all

.PHONY: all clean fclean re
