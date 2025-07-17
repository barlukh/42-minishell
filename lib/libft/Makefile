# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 10:50:25 by bgazur            #+#    #+#              #
#    Updated: 2025/07/17 11:14:38 by bgazur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libft.a

COMPILER =		cc
CFLAGS =		-Wall -Wextra -Werror
AR =			ar rcs
RM =			rm -rf

DIR_HDR =		include
DIR_OBJ =		objects
DIR_SRC =		src

HDR =			$(DIR_HDR)/libft.h
OBJ =			$(SRC:%.c=$(DIR_OBJ)/%.o)
SRC = 			ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_memset.c  \
				ft_bzero.c \
				ft_memcpy.c  \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \
				ft_free_array.c

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJ)
	@$(AR) $@ $^
	@echo "✅ Build $(GREEN)$(NAME) $(NC)successfully! 🎉"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)
	@echo "📁 Creating directory for $(NAME) objects"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HDR)
	@$(COMPILER) $(CFLAGS) -I $(DIR_HDR) -c $< -o $@
	@echo "... 🛠️ compiling $<"

clean:
	@$(RM) $(DIR_OBJ)
	@echo "🧹 Objects of $(NAME) are removed! -> 🗑️"

fclean: clean
	@$(RM) $(NAME)
	@echo "🧹 Executable $(NAME) is removed! -> 🗑️ "

re: fclean all

.PHONY: all clean fclean re
