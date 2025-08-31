# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 08:53:07 by bgazur            #+#    #+#              #
#    Updated: 2025/08/31 11:41:46 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
CFLAGS		=	-g2 -Wall -Werror -Wextra
LFLAGS		=	-L$(DIR_LIBFT) -lft -lreadline
RM			=	rm -rf

DIR_LIBFT	=	lib/libft
DIR_HDR		=	include
DIR_OBJ		=	objects
DIR_SRC		=	src
DIR_BUILTIN	=	$(DIR_SRC)/builtins
DIR_EXEC	=	$(DIR_SRC)/execution
DIR_HEREDOC	=	$(DIR_SRC)/heredocs
DIR_PARSING	=	$(DIR_SRC)/parsing
DIR_SIGNALS	=	$(DIR_SRC)/signals

LIBFT		=	$(DIR_LIBFT)/libft.a
HDR			=	$(DIR_HDR)/minishell.h
OBJ			=	$(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)
SRC			=	$(DIR_BUILTIN)/builtin_cd_utils.c \
				$(DIR_BUILTIN)/builtin_cd.c \
				$(DIR_BUILTIN)/builtin_echo.c \
				$(DIR_BUILTIN)/builtin_env.c \
				$(DIR_BUILTIN)/builtin_exit.c \
				$(DIR_BUILTIN)/builtin_export_utils.c \
				$(DIR_BUILTIN)/builtin_export.c \
				$(DIR_BUILTIN)/builtin_pwd_utils.c \
				$(DIR_BUILTIN)/builtin_pwd.c \
				$(DIR_BUILTIN)/builtin_unset.c \
				$(DIR_BUILTIN)/builtins.c \
				$(DIR_EXEC)/execution_utils.c \
				$(DIR_EXEC)/execution.c \
				$(DIR_EXEC)/path.c \
				$(DIR_EXEC)/pipe.c \
				$(DIR_EXEC)/wrappers.c \
				$(DIR_EXEC)/wait.c \
				$(DIR_EXEC)/builtin.c \
				$(DIR_HEREDOC)/errors_heredocs.c \
				$(DIR_HEREDOC)/exp_exit_heredoc.c \
				$(DIR_HEREDOC)/heredocs_expander.c \
				$(DIR_HEREDOC)/heredocs_utils.c \
				$(DIR_HEREDOC)/heredocs.c \
				$(DIR_PARSING)/ambiguous_redir.c \
				$(DIR_PARSING)/env_expander_utils.c \
				$(DIR_PARSING)/env_expander.c \
				$(DIR_PARSING)/env_utils.c \
				$(DIR_PARSING)/errors_parsing.c \
				$(DIR_PARSING)/exp_exit_main.c \
				$(DIR_PARSING)/heredoc_identifier.c \
				$(DIR_PARSING)/input.c \
				$(DIR_PARSING)/merger_utils.c \
				$(DIR_PARSING)/merger.c \
				$(DIR_PARSING)/parsing_finalizer.c \
				$(DIR_PARSING)/quote_remover.c \
				$(DIR_PARSING)/syntax_checker.c \
				$(DIR_PARSING)/tokenizer.c \
				$(DIR_PARSING)/word_splitter.c \
				$(DIR_SIGNALS)/signals_exec_child.c \
				$(DIR_SIGNALS)/signals_exec_parent.c \
				$(DIR_SIGNALS)/signals_heredoc.c \
				$(DIR_SIGNALS)/signals_readline.c \
				$(DIR_SRC)/main.c

all: $(DIR_OBJ) $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@echo "✅ Build $(GREEN)$(NAME) $(NC)successfully! 🎉"

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)
	@echo "📁 Creating directory for $(NAME) objects"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(DIR_HDR) -I$(DIR_LIBFT)/include -c $< -o $@

clean:
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT) clean
	@$(RM) $(DIR_OBJ)
	@echo "🧹 Objects of $(NAME) are removed! -> 🗑️"

fclean:
	@$(MAKE) --no-print-directory -C $(DIR_LIBFT) fclean
	@$(RM) $(DIR_OBJ)
	@echo "🧹 Objects of $(NAME) are removed! -> 🗑️"
	@$(RM) $(NAME)
	@echo "🧹 Executable $(NAME) is removed! -> 🗑️ "

re: fclean all

.PHONY: all clean fclean re
