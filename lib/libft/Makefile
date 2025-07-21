# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 10:50:25 by bgazur            #+#    #+#              #
#    Updated: 2025/07/21 08:46:47 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libft.a

CC =			cc
CFLAGS =		-Wall -Wextra -Werror
AR =			ar rcs
RM =			rm -rf

DIR_HDR =		include
DIR_OBJ =		objects
DIR_SRC =		src

HDR =			$(DIR_HDR)/libft.h
OBJ =			$(SRC:%.c=$(DIR_OBJ)/%.o)

SRC = 			ft_bzero.c \
				ft_calloc.c \
				ft_free_array.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdelimiter.c \
				ft_isdigit.c \
				ft_isifs.c \
				ft_isprint.c \
				ft_isquote.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstlast.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_memcpy.c  \
				ft_memset.c  \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJ)
	@$(AR) $@ $^
	@echo "✅ Build $(GREEN)$(NAME) $(NC)successfully! 🎉"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)
	@echo "📁 Creating directory for $(NAME) objects"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HDR)
	@$(CC) $(CFLAGS) -I $(DIR_HDR) -c $< -o $@
	@echo "... 🛠️ compiling $<"

clean:
	@$(RM) $(DIR_OBJ)
	@echo "🧹 Objects of $(NAME) are removed! -> 🗑️"

fclean: clean
	@$(RM) $(NAME)
	@echo "🧹 Executable $(NAME) is removed! -> 🗑️ "

re: fclean all

.PHONY: all clean fclean re
