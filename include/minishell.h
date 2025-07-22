/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:41:27 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/22 15:52:59 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include "../lib/libft/include/libft.h"

# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

# include <stdio.h> // UNUSED, REMOVE BEFORE SUBMISSION !!!!!!!!!!!!!!!!!!!!!

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

// Exit values.
# define SUCCESS 0
# define FAILURE 1
# define ERR_SYNTAX 2

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Copies environment variables, storing them as a linked list.
 * @param env Environment variables.
 * @param lst_env Pointer to the head pointer of a linked list of env variables.
 * @return None.
 */
void	create_lst_env(char **env, t_env **lst_env);

/**
 * @brief Handles errors when creating list of environment variables.
 * @param lst_env Pointer to the head pointer of a linked list of env variables.
 * @return Exit code.
 */
int		error_lst_env(t_env **lst_env);

/**
 * @brief Handles errors in parsing phase.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return Exit code.
 */
int		error_parser(t_token **lst_tok);

/**
 * @brief Handles errors in tokenizing phase.
 * @param input Input string received from a command line.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @return Exit code.
 */
int		error_tokenizer(char *input, t_token **lst_tok, t_env **lst_env);

/**
 * @brief Parses command line input string with tokenizer and parser.
 * @param input Input string received from a command line.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @return None.
 */
void	parse_input(char *input, t_token **lst_tok, t_env **lst_env);

/**
 * @brief Parses tokens created by tokenizer.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @return None.
 */
void	parser(t_token **lst_tok, t_env **env);

/**
 * @brief Reads input from a command line.
 * @param input Pointer to a string in which to store the input.
 * @return None.
 */
void	read_input(char **input);

/**
 * @brief Tokenizes command line input string.
 * @param input Input string received from a command line.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @return None.
 */
void	tokenizer(char *input, t_token **lst_tok, t_env **lst_env);

#endif
