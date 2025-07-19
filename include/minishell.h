/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:41:27 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/19 13:58:18 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include "../lib/libft/include/libft.h"

# include <readline/readline.h>
# include <stdbool.h>

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

# define DELIMS "|&<> \t\n"

# define SUCCESS 0

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Handles errors in tokenizing phase.
 * @param input_line Input string received from a command line.
 * @param lst Pointer to the head pointer of a linked list of tokens.
 * @param content Allocated substring from the input_line.
 * @return Exit code.
 */
int		error_tok(char *input_line, t_token **lst, char *content);

/**
 * @brief Parses command line input string.
 * @param input_line Input string received from a command line.
 * @param lst Pointer to the head pointer of a linked list of tokens.
 * @return None.
 */
void	parse_input(char *input_line, t_token **lst);

/**
 * @brief Reads input from a command line.
 * @param input_line Pointer to a string in which to store the input.
 * @return None.
 */
void	read_input(char **input_line);

/**
 * @brief Tokenizes command line input string.
 * @param input_line Input string received from a command line.
 * @param lst Pointer to the head pointer of a linked list of tokens.
 * @return None.
 */
void	tokenizer(char *input_line, t_token **lst);

#endif
