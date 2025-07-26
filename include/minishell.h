/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:41:27 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/26 16:08:46 by bgazur           ###   ########.fr       */
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

// Error messages.
# define ERR_MSG_ENV "Corrupted environment variables"
# define ERR_MSG_MEM "Error allocating memory"
# define ERR_MSG_SYN "Syntax error"

// Error / exit values.
# define SUCCESS 0
# define FAILURE 1
# define INV_SYNTAX 2

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
 * @brief Handles errors when creating a linked list of environment variables.
 * @param err Error value.
 * @param key Key string.
 * @param value Value string.
 * @param lst_env Pointer to the head pointer of a linked list of env variables.
 * @return Exit code.
 */
int		error_lst_env(int err, char *key, char *value, t_env **lst_env);

/**
 * @brief Handles errors in parsing phase.
 * @param err Error value.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return Exit code.
 */
int		error_par(int err, t_env **lst_env, t_token **lst_tok);

/**
 * @brief Handles errors in tokenizing phase.
 * @param err Error value.
 * @param input Input string received from a command line.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return Exit code.
 */
int		error_tok(int err, char *input, t_env **lst_env, t_token **lst_tok);

/**
 * @brief Peforms environment variable expansion.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return SUCCESS or FAILURE.
 */
bool	env_expander(t_env **env, t_token **lst_tok);

/**
 * @brief Parses command line input string.
 * @param input Input string received from a command line.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return None.
 */
void	parse_input(char *input, t_env **lst_env, t_token **lst_tok);

/**
 * @brief Removes quotes in tokens.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return None.
 */
void	quote_remover(t_token **lst_tok);

/**
 * @brief Reads input from a command line.
 * @param input Pointer to a string in which to store the input.
 * @return None.
 */
void	read_input(char **input);

/**
 * @brief Checks for syntax errors in tokens.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return SUCCESS or FAILURE.
 */
bool	syntax_checker(t_token **lst_tok);

/**
 * @brief Tokenizes command line input string.
 * @param input Input string received from a command line.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return SUCCESS or FAILURE.
 */
bool	tokenizer(char *input, t_token **lst_tok);

#endif
