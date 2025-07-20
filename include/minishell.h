/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:41:27 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/20 12:26:10 by bgazur           ###   ########.fr       */
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

# define DELIMITERS "|&<>"

# define SUCCESS 0

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

// Quotes state enumeration.
typedef enum e_quotes_state
{
	QUOTES_IN,
	QUOTES_OUT
}	t_quotes_state;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Handles errors in tokenizing phase.
 * @param input Input string received from a command line.
 * @param lst Pointer to the head pointer of a linked list of tokens.
 * @param content Allocated substring from the input.
 * @return Exit code.
 */
int		error_tok(char *input, t_token **lst, char *content);

/**
 * @brief Parses command line input string.
 * @param input Input string received from a command line.
 * @param lst Pointer to the head pointer of a linked list of tokens.
 * @return None.
 */
void	parse_input(char *input, t_token **lst);

/**
 * @brief Reads input from a command line.
 * @param input Pointer to a string in which to store the input.
 * @return None.
 */
void	read_input(char **input);

/**
 * @brief Tokenizes command line input string.
 * @param input Input string received from a command line.
 * @param lst Pointer to the head pointer of a linked list of tokens.
 * @return None.
 */
void	tokenizer(char *input, t_token **lst);

#endif
