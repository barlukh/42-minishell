# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 08:53:07 by bgazur            #+#    #+#              #
#    Updated: 2025/07/29 11:41:01 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address -fsanitize=undefined -fsanitize=leak
LFLAGS		=	-L$(DIR_LIBFT) -lft -lreadline
RM			=	rm -rf

DIR_LIBFT	=	lib/libft
DIR_HDR		=	include
DIR_OBJ		=	objects
DIR_SRC		=	src
DIR_BUILTIN	=	$(DIR_SRC)/builtins
DIR_EXEC	=	$(DIR_SRC)/execution
DIR_PARSING	=	$(DIR_SRC)/parsing

LIBFT		=	$(DIR_LIBFT)/libft.a
HDR			=	$(DIR_HDR)/minishell.h
OBJ			=	$(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)
SRC			=	$(DIR_BUILTIN)/builtin_cd.c \
				$(DIR_BUILTIN)/builtin_echo.c \
				$(DIR_BUILTIN)/builtins.c \
				$(DIR_EXEC)/temporary.c \
				$(DIR_PARSING)/env_expander.c \
				$(DIR_PARSING)/env_utils.c \
				$(DIR_PARSING)/errors_parsing.c \
				$(DIR_PARSING)/input.c \
				$(DIR_PARSING)/quote_remover.c \
				$(DIR_PARSING)/syntax_checker.c \
				$(DIR_PARSING)/tokenizer.c \
				$(DIR_SRC)/main.c

all: $(DIR_OBJ) $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "✅ Build $(GREEN)$(NAME) $(NC)successfully! 🎉"

$(LIBFT):
	@$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)
	@echo "📁 Creating directory for $(NAME) objects"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(DIR_HDR) -I$(DIR_LIBFT)/include -c $< -o $@
	@echo "... 🛠️ compiling $<"

clean:
	@$(MAKE) -C $(DIR_LIBFT) clean
	@$(RM) $(DIR_OBJ)
	@echo "🧹 Objects of $(NAME) are removed! -> 🗑️"

fclean:
	@$(MAKE) -C $(DIR_LIBFT) fclean
	@$(RM) $(DIR_OBJ)
	@echo "🧹 Objects of $(NAME) are removed! -> 🗑️"
	@$(RM) $(NAME)
	@echo "🧹 Executable $(NAME) is removed! -> 🗑️ "

re: fclean all

.PHONY: all clean fclean re
