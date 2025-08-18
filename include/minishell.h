/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:41:27 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/18 11:34:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include "libft.h"

# include <stdio.h> // UNUSED, REMOVE BEFORE SUBMISSION !!!!!!!!!!!!!!!!!!!!!
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>


//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

extern volatile sig_atomic_t	g_signal;

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

// Maximum length of a valid input for readline.
# define INPUT_MAX 1024

// Maximum number of bytes allowed in a full pathname.
# define PATH_MAX 4096

// Temp files naming prefix.
# define TEMP "here_temp"

// Error messages.
# define ERR_MSG_AMB "redirection: ambiguous redirect"
# define ERR_MSG_ENV "env: options and arguments are not supported"
# define ERR_MSG_EOF "warning: here-document delimited by end-of-file"
# define ERR_MSG_EXIT "exit"
# define ERR_MSG_FILE "open: Error opening file"
# define ERR_MSG_HERE "maximum here-document count exceeded"
# define ERR_MSG_INPUT "maximum input length exceeded"
# define ERR_MSG_MEM "malloc: Cannot allocate memory"
# define ERR_MSG_NUMARG "exit: numeric argument required"
# define ERR_MSG_PIPES "syntax error near unexpected token `|\'"
# define ERR_MSG_PWD "pwd: options are not supported"
# define ERR_MSG_QUOTE "syntax error: unclosed quote"
# define ERR_MSG_REDIR "syntax error near unexpected token `redirection'"
# define ERR_MSG_TOOARG "exit: too many arguments"

// Return / exit values (general).
# define SUCCESS 0
# define FAILURE 1

// Return / exit values (builtins).
# define BUILT_NO 0
# define BUILT_YES 1

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

// Data struct of all core variables.
typedef struct s_data
{
	int		exit_status;
	size_t	cmd_count;
	t_env	*lst_env;
	t_token	*lst_tok;
	t_exec	*lst_exec;
}	t_data;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Checks if the file name contains a space character.
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	ambiguous_redir(t_data *data);

/**
 * @brief Tries to execute the cd builtin.
 * @param current Current token.
 * @return Bool true or false.
 */
bool	builtin_cd(t_exec *current);

/**
 * @brief Tries to execute the echo builtin.
 * @param current Current token.
 * @return Bool true or false.
 */
bool	builtin_echo(t_exec *current);

/**
 * @brief Tries to execute the env builtin.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	builtin_env(t_exec *current, t_data *data);

/**
 * @brief Tries to execute the exit builtin.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	builtin_exit(t_exec *current, t_data *data);

/**
 * @brief Tries to execute the pwd builtin.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	builtin_pwd(t_exec *current, t_data *data);

/**
 * @brief Checks if the current token is a builtin command.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	builtins_check(t_exec *current, t_data *data);

/**
 * @brief Frees all allocated memory in the data struct.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	clean_data(t_data *data);

/**
 * @brief Frees allocated memory when merger fails.
 * @param node Current node.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	clean_merge(t_exec *node, t_data *data);

/**
 * @brief Creates heredocs.
 * @param data Data struct of all core variables.
 * @return SUCCESS or FAILURE.
 */
bool	create_heredocs(t_data *data);

/**
 * @brief Copies environment variables, storing them as a linked list.
 * @param env Environment variables.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	create_lst_env(char **env, t_data *data);

/**
 * @brief Peforms an environment variable expansion.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	env_expander(t_data *data);

/**
 * @brief Handles general memory errors.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	error_general_mem(t_data *data);

/**
 * @brief Handles errors in heredoc variable expansion.
 * @param input Input string received from a command line.
 * @param fd Open file descriptor of the current file.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	error_heredoc_exp(char *input, int *fd, t_data *data);

/**
 * @brief Handles errors with heredoc file fails.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	error_heredoc_file(t_data *data);

/**
 * @brief Handles errors with heredoc memory fails.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	error_heredoc_mem(t_data *data);

/**
 * @brief Handles heredoc signal interrupts.
 * @param data Data struct of all core variables.
 * @return FAILURE.
 */
bool	error_heredoc_signal(t_data *data);

/**
 * @brief Handles errors when creating a linked list of environment variables.
 * @param key Key string.
 * @param value Value string.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	error_lst_env(char *key, char *value, t_data *data);

/**
 * @brief Handles errors in the syntax checking phase.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	error_synt(t_data *data);

/**
 * @brief Handles errors in the tokenizing phase.
 * @param input Input string received from a command line.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	error_tok(char *input, t_data *data);

/**
 * @brief Executes parsed tokens.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	execution(t_data *data);

/**
 * @brief Expands question mark variable in a heredoc.
 * @param input Address of the input string received from a command line.
 * @param tok_key Key string.
 * @param i Index of a character.
 * @param data Data struct of all core variables.
 * @return SUCCESS or FAILURE.
 */
bool	exp_exit_heredoc(char **input, char *tok_key, size_t i, t_data *data);

/**
 * @brief Expands question mark variable in a token.
 * @param content Pointer to the content of the current token.
 * @param tok_key Key string.
 * @param i Index of a character.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	exp_exit_main(char **content, char *tok_key, size_t i, t_data *data);

/**
 * @brief Expands variables and writes the input into a file.
 * @param input Input string received from a command line.
 * @param fd Open file descriptor of the current file.
 * @param current Current token.
 * @param data Data struct of all core variables.
 */
void	expand_write(char *input, int *fd, t_token *current, t_data *data);

/**
 * @brief Creates a static data struct.
 * @param void None.
 * @return Pointer to the data struct.
 */
t_data	*get_data(void);

/**
 * @brief Function to call periodically when readline is waiting for input.
 * @param void None.
 * @return None.
 */
int		heredoc_event_hook(void);

/**
 * @brief Identifies quotes in a heredoc delimiter and reassigns token type.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	heredoc_identifier(t_data *data);

/**
 * @brief Writes an input line into a heredoc.
 * @param input Input string received from a command line.
 * @param fd Open file descriptor of the current file.
 * @return None.
 */
void	heredoc_write(char *input, int *fd);

/**
 * @brief Merges parsed tokens into grouped up tokens separated by pipes.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	merger(t_data *data);

/**
 * @brief Parses command line input string.
 * @param input Input string received from a command line.
 * @param data Data struct of all core variables.
 * @return SUCCESS or FAILURE.
 */
bool	parse_input(char *input, t_data *data);

/**
 * @brief Finalizes the parsed list - removes empty tokens and identifies words.
 * @param current NULL.
 * @param data Data struct of all core variables.
 * @return SUCCESS or FAILURE.
 */
int		parsing_finalizer(t_token *current, t_data *data);

/**
 * @brief Removes quotes in tokens.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	quote_remover(t_data *data);

/**
 * @brief Reads input from the command line.
 * @param input Pointer to a string in which to store the input.
 * @param data Data struct of all core variables.
 * @return SUCCESS or FAILURE.
 */
bool	read_input(char **input, t_data *data);

/**
 * @brief Renames heredoc token with the file name.
 * @param i Index of a file.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	rename_heredoc_token(size_t i, t_token *current, t_data *data);

/**
 * @brief Executes when a signal is received in heredoc.
 * @param signum Signal number.
 * @return None.
 */
void	signal_handler_heredoc(int signum);

/**
 * @brief Executes when a signal is received in the main process.
 * @param signum Signal number.
 * @return None.
 */
void	signal_handler_main(int signum);

/**
 * @brief Defines behaviour of signals in heredoc.
 * @param void None.
 * @return None.
 */
void	signals_heredoc(void);

/**
 * @brief Defines behaviour of signals in the main processs.
 * @param void None.
 * @return None.
 */
void	signals_main(void);

/**
 * @brief Checks for syntax errors in tokens.
 * @param data Data struct of all core variables.
 * @return SUCCESS or FAILURE.
 */
bool	syntax_checker(t_data *data);

/**
 * @brief Tokenizes command line input string.
 * @param input Input string received from a command line.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	tokenizer(char *input, t_data *data);

/**
 * @brief Replaces variables with their expanded values (quoted).
 * @param content Pointer to the content of the current token.
 * @param new_cont Pointer to the malloc for the new content.
 * @param i Index of a character.
 * @param current Current environment variable.
 * @return None.
 */
void	var_exp_q(char *content, char *new_cont, size_t *i, t_env *current);

/**
 * @brief Replaces variables with their expanded values (unquoted).
 * @param content Pointer to the content of the current token.
 * @param new_cont Pointer to the malloc for the new content.
 * @param i Index of a character.
 * @param current Current environment variable.
 * @return None.
 */
void	var_exp_u(char *content, char *new_cont, size_t *i, t_env *current);

/**
 * @brief Removes environment variables that have no values.
 * @param content Pointer to the content of the current token.
 * @param tok_key Key string.
 * @param i Index of a character.
 * @return None.
 */
void	var_remove(char *content, char **tok_key, size_t i);

/**
 * @brief Performs word splitting on expanded variables.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	word_splitter(t_data *data);

#endif
