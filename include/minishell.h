/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:41:27 by bgazur            #+#    #+#             */
/*   Updated: 2025/09/04 16:22:59 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include "libft.h"

# include <stdio.h> // UNUSED, REMOVE BEFORE SUBMISSION !!!!!!!!!!!!!!!!!!!!!
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

extern volatile sig_atomic_t	g_signal;

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

// Maximum length of a valid input for readline.
# define INPUT_MAX 1024

// Temp files naming prefix.
# define TEMP "/tmp/here_temp"

// Error messages.
# define ERR_MSG_AMB "redirection: ambiguous redirect"
# define ERR_MSG_CD "cd: options are not supported"
# define ERR_MSG_CDARG "cd: too many arguments"
# define ERR_MSG_CDFILE "cd: file name too long"
# define ERR_MSG_CDSET "cd: OLDPWD not set"
# define ERR_MSG_CDHOME "cd: HOME not set"
# define ERR_MSG_ENV "env: options and arguments are not supported"
# define ERR_MSG_EOF "warning: here-document delimited by end-of-file"
# define ERR_MSG_EXARG "exit: too many arguments"
# define ERR_MSG_EXIT "exit"
# define ERR_MSG_EXPORT "export: options are not supported"
# define ERR_MSG_FILE "open: Error opening file"
# define ERR_MSG_HERE "maximum here-document count exceeded"
# define ERR_MSG_IDEN "export: not a valid identifier"
# define ERR_MSG_INPUT "maximum input length exceeded"
# define ERR_MSG_MEM "malloc: Cannot allocate memory"
# define ERR_MSG_NUMARG "exit: numeric argument required"
# define ERR_MSG_PIPES "syntax error near unexpected token `|\'"
# define ERR_MSG_PWD "pwd: options are not supported"
# define ERR_MSG_QUOTE "syntax error: unclosed quote"
# define ERR_MSG_REDIR "syntax error near unexpected token `redirection'"
# define ERR_MSG_UNSET "unset: options are not supported"
# define ERR_MSG_DUP "dup: failure"

// Return / exit values (general).
# define SUCCESS 0
# define FAILURE 1

// Return / exit values (builtins).
# define BUILT_NO 0
# define BUILT_YES 1

// fd values (execution).
# define READ 0
# define WRITE 1
//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

// Data struct of all core variables.
typedef struct s_data
{
	int		exit_status;
	int		tok_count;
	t_env	*lst_env;
	t_token	*lst_tok;
	t_exec	*lst_exec;
	int		tmp_fd;
	pid_t	*pids;
	char	**env;
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
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	builtin_cd(t_exec *current, t_data *data);

/**
 * @brief Tries to execute the echo builtin.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	builtin_echo(t_exec *current, t_data *data);

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
 * @brief Tries to execute the export builtin.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	builtin_export(t_exec *current, t_data *data);

/**
 * @brief Main function to export a variable.
 * @param inv_id Flag to signal a succesful export.
 * @param con Content to export.
 * @param node Current token node.
 * @param data Data struct of all core variables.
 */
void	builtin_exp_loop(bool *inv_id, char *con, t_exec *node, t_data *data);

/**
 * @brief Tries to execute the pwd builtin.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	builtin_pwd(t_exec *current, t_data *data);

/**
 * @brief Tries to execute the unset builtin.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return Bool true or false.
 */
bool	builtin_unset(t_exec *current, t_data *data);

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
 * @brief Gets and returns the HOME value from env.
 * @param data Data struct of all core variables.
 * @return HOME or NULL if not found.
 */
char	*home_get(t_data *data);

/**
 * @brief Merges parsed tokens into grouped up tokens separated by pipes.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	merger(t_data *data);

/**
 * @brief Gets and returns the OLDPWD value from env.
 * @param data Data struct of all core variables.
 * @return OLDPWD or NULL if not found.
 */
char	*oldpwd_get(t_data *data);

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
 * @brief Allocates memory for an array of append redirections.
 * @param node New token node.
 * @param current Current token node.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	prep_app(t_exec *node, t_token *current, t_data *data);

/**
 * @brief Allocates memory for an array of commands and arguments.
 * @param node New token node.
 * @param current Current token node.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	prep_cmd_arg(t_exec *node, t_token *current, t_data *data);

/**
 * @brief Allocates memory for an array of redirections in.
 * @param node New token node.
 * @param current Current token node.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	prep_in(t_exec *node, t_token *current, t_data *data);

/**
 * @brief Allocates memory for an array of redirections out.
 * @param node New token node.
 * @param current Current token node.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	prep_out(t_exec *node, t_token *current, t_data *data);

/**
 * @brief Gets and returns the malloced PWD value from env.
 * @param data Data struct of all core variables.
 * @param node Current token node.
 * @return PWD or NULL if not found.
 */
char	*pwd_get(t_data *data, t_exec *node);

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
 * @brief Receives input from readline() or get_next_line().
 * @param input Pointer to received input.
 * @param prompt String to print on the terminal prompt.
 * @return None.
 */
void	receive_input(char **input, char *prompt);

/**
 * @brief Renames heredoc token with the file name.
 * @param i Index of a file.
 * @param current Current token.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	rename_heredoc_token(size_t i, t_token *current, t_data *data);

/**
 * @brief Defines behaviour of signals in execution child path.
 * @param void None.
 * @return None.
 */
void	signals_exec_child(void);

/**
 * @brief Defines behaviour of signals in execution parent path.
 * @param void None.
 * @return None.
 */
void	signals_exec_parent(void);

/**
 * @brief Defines behaviour of signals in heredoc.
 * @param void None.
 * @return None.
 */
void	signals_heredoc(void);

/**
 * @brief Defines behaviour of signals in the readline prompt.
 * @param void None.
 * @return None.
 */
void	signals_readline(void);

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
 * @brief Sets the PWD and OLDPWD values in env.
 * @param cwd Current working directory.
 * @param current Current token node.
 * @param data Data struct of all core variables.
 * @return True.
 */
bool	wd_set(char *cwd, t_exec *current, t_data *data);

/**
 * @brief Performs word splitting on expanded variables.
 * @param data Data struct of all core variables.
 * @return None.
 */
void	word_splitter(t_data *data);

/* ************************************************************************** */

/**
 * @brief Check if a given command is a builtin. 
 * @param command command of the current node.
 * @return true if is a bultin, false otherwise
 */
bool	is_builtins(char **command);

/**
 * @brief Sets the correct order of opening fds
 * @param node Pointer to the current node.
 * @param i Counter of the current node on the pipeline.
 * @return True if no error found.
 */
bool	open_fds(t_exec *node, int i);

/**
 * @brief Iterate to the infiles to be open.
 * @param node Pointer to the current node.
 * @return True on succesfully opening fds.
 */
bool	open_fds_in(t_exec *node);

/**
 * @brief Iterate to the outfiles to be open.
 * @param node Pointer to the current node.
 * @return True on succesfully opening fds.
 */
bool	open_fds_out(t_exec *node);

/**
 * @brief Open the infile.
 * @param node Pointer to the current node.
 * @param j Index of the infile on current node.
 * @return True on succesfully opening fd.
 */
bool	safe_open_in(t_exec *node, int j);

/**
 * @brief Open the outfile.
 * @param node Pointer to the current node.
 * @param j Index of the outfile on current node.
 * @return True on succesfully opening fd.
 */
bool	safe_open_out(t_exec *node, int j);

/**
 * @brief Wait for the result of all child processes
 * @param pid Pointer to the array o child's pid numbers
 * @param data Pointer to data structure.
 * @return True success.
 */
bool	wait_process(pid_t *pid, t_data *data);

/**
 * @brief Retrieve from environment path and join the command
 * @param command Command on current node.
 * @param env enviroment path
 * @return The full path of the command called.
 */
char	*path_finder(char **command, char **env);

/**
 * @brief Rebuild the enviroment on the current pipeline
 * @param data Pointer to data structure.
 * @return The environment path.
 */
char	**rebuild_env(t_data *data);

/**
 * @brief Execute the builtin command on a pipeline or alone. 
 * @param node Pointer to the current node.
 * @param i index of current command on the pipeline.
 * @param data Pointer to the data structure.
 * @return zero on success.
 */
int		builtin_process(t_exec *node, int i, t_data *data);

/**
 * @brief Redirect the command to correct fds.
 * @param node Pointer to the current node.
 * @param i index of current command on the pipeline.
 * @return zero on success.
 */
int		redirections_builtin(t_exec *node, int i);

/**
 * @brief Redirect infile and outfiles of the subprocess.
 * @param node Pointer to the current node.
 * @param i index of current command on the pipeline.
 * @return zero on success.
 */
int		redirections_io(t_exec *node, int i);

/**
 * @brief Close the fd and set to -1.
 * @param fd Pointer to the fd.
 * @return Pointer to fd.
 */
int		safe_close(int *fd);

/**
 * @brief Dup the oldfd to the newfd and close the oldfd.
 * @param oldfd fd to be dup to stdin or stdout
 * @param newfd stdin or stdout
 * @return newfd.
 */
int		safe_dup(int *oldfd, int newfd);

/**
 * @brief Check if the path does not have permissions or don't exist 
 * @param is_path command on the current node.
 * @param node Pointer to the current node.
 * @param data Pointer to the data structure.
 */
void	check_access(char *is_path, t_exec *node, t_data *data);

/**
 * @brief Print the message of command not found.
 * @param node Pointer to the current node.
 * @param data Pointer to the data structure.
 */
void	check_cmd(t_exec *node, t_data *data);

/**
 * @brief Print if command is a directory or . or not found.
 * @param is_path command on the current node.
 * @param node Pointer to the current node.
 * @param data Pointer to the data structure.
 */
void	check_dir(char *is_path, t_exec *node, t_data *data);

/**
 * @brief Print the message of command not found.
 * @param node Pointer to the current node.
 * @param data Pointer to the data structure.
 */
void	check_empty(t_exec *node, t_data *data);

/**
 * @brief Execute the command on a child subprocess. 
 * @param node Pointer to the current node.
 * @param i index of current command on the pipeline.
 * @param data Pointer to the data structure.
 */
void	child_process(t_exec *node, int i, t_data *data);

/**
 * @brief Clean all the structures and return the exit code
 * @param node Pointer to the current node.
 * @param data Pointer to the data structure.
 * @param exit_code exit code of the process.
 */
void	clean_and_exit(t_data *data, t_exec *node, int exit_code);

/**
 * @brief Close all fds that are not closed.
 * @param data Pointer to the data structure.
 * @param node Pointer to the current node.
 */
void	close_all_fds(t_data *data, t_exec *node);

/**
 * @brief Restore fds stdin and stdout.
 * @param node Pointer to the current node.
 */
void	restore_fds(t_exec *node);

/**
 * @brief Create a a builtin or a child subprocess
 * @param data Pointer to the data structure.
 * @param node Pointer to the current node.
 * @param i counter of current command on the pipeline.
 */
void	create_process(t_data *data, t_exec *node, int i);

/**
 * @brief Begin the execution process.
 * @param node Pointer to the data structure.
 */
void	execution(t_data *data);

/**
 * @brief Close fds and update the tmp_fd on data structure.
 * @param node Pointer to the current node.
 */
void	parent_fds(t_exec *node);

#endif
