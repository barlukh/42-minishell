/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:41:27 by bgazur            #+#    #+#             */
/*   Updated: 2025/07/29 11:50:08 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include "libft.h"

# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

# include <stdio.h> // UNUSED, REMOVE BEFORE SUBMISSION !!!!!!!!!!!!!!!!!!!!!

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

// Maximum number of bytes allowed in a full pathname.
# define PATH_MAX 4096

// Error messages.
# define ERR_MSG_MEM "malloc: Cannot allocate memory"
# define ERR_MSG_QUOTE "syntax error: unclosed quote"
# define ERR_MSG_PIPES "syntax error near unexpected token `|\'"
# define ERR_MSG_REDIR "syntax error near unexpected token `>\'"
# define ERR_MSG_HERED "maximum here-document count exceeded"

// Return / exit values (general).
# define SUCCESS 0
# define FAILURE 1
# define INV_SYNTAX 2

// Return / exit values (builtins).
# define BUILT_NO 0
# define BUILT_YES 1
# define BUILT_ERR 2

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Tries to execute the cd builtin.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param current Pointer to a pointer of the current token.
 * @return Integer signaling whether token is a builtin, or error on execution.
 */
int		builtin_cd(t_env **lst_env, t_token **current);

/**
 * @brief Tries to execute the echo builtin.
 * @param current Pointer to a pointer of the current token.
 * @return Integer signaling whether token is a builtin, or error on execution.
 */
int		builtin_echo(t_token **current);

/**
 * @brief Checks if the current token is a builtin command.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param current Pointer to a pointer of the current token.
 * @return Integer signaling whether token is a builtin, or error on execution.
 */
int		builtins_check(t_env **lst_env, t_token **current);

/**
 * @brief Copies environment variables, storing them as a linked list.
 * @param env Environment variables.
 * @param lst_env Pointer to the head pointer of a linked list of env variables.
 * @return None.
 */
void	create_lst_env(char **env, t_env **lst_env);

/**
 * @brief Peforms an environment variable expansion.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return SUCCESS or FAILURE.
 */
bool	env_expander(t_env **env, t_token **lst_tok);

/**
 * @brief Handles errors in the environment expansion phase.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return Exit code.
 */
int		error_env_exp(t_env **lst_env, t_token **lst_tok);

/**
 * @brief Handles errors when creating a linked list of environment variables.
 * @param key Key string.
 * @param value Value string.
 * @param lst_env Pointer to the head pointer of a linked list of env variables.
 * @return Exit code.
 */
int		error_lst_env(char *key, char *value, t_env **lst_env);

/**
 * @brief Handles errors is the syntax check phase.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return Exit code.
 */
int		error_synt(t_env **lst_env, t_token **lst_tok);

/**
 * @brief Handles errors in the tokenizing phase.
 * @param input Input string received from a command line.
 * @param lst_env Pointer to the head pointer of a linked list of env vars.
 * @param lst_tok Pointer to the head pointer of a linked list of tokens.
 * @return Exit code.
 */
int		error_tok(char *input, t_env **lst_env, t_token **lst_tok);

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
 * @brief Reads input from the command line.
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
