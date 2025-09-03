/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 07:52:40 by bgazur            #+#    #+#             */
/*   Updated: 2025/09/03 10:40:20 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	read_input(char **input, t_data *data)
{
	receive_input(input, "minishell$ ");
	if (!*input)
	{
		ft_lst_env_clear(&data->lst_env);
		clear_history();
		// ft_putendl_fd(ERR_MSG_EXIT, STDOUT_FILENO); //commented for big test
		exit(data->exit_status);
	}
	if (ft_strlen(*input) > INPUT_MAX)
	{
		data->exit_status = 2;
		ft_putendl_fd(ERR_MSG_INPUT, STDERR_FILENO);
		free(*input);
		return (FAILURE);
	}
	add_history(*input);
	return (SUCCESS);
}

void	receive_input(char **input, char *prompt)
{
	char	*line;

	if (isatty(fileno(stdin)))
		*input = readline(prompt); //all the other lines for small test
	else
	{
		line = get_next_line(fileno(stdin));
		if (!line)
			*input = NULL;
		else
		{
			*input = ft_strtrim(line, "\n");
			free(line);
		}
	}
}

bool	parse_input(char *input, t_data *data)
{
	tokenizer(input, data);
	if (syntax_checker(data) != SUCCESS)
	{
		ft_lst_tok_clear(&data->lst_tok);
		data->exit_status = 2;
		return (FAILURE);
	}
	env_expander(data);
	if (ambiguous_redir(data))
	{
		ft_lst_tok_clear(&data->lst_tok);
		data->exit_status = 1;
		return (FAILURE);
	}
	heredoc_identifier(data);
	word_splitter(data);
	quote_remover(data);
	if (parsing_finalizer(NULL, data) != SUCCESS)
	{
		ft_lst_tok_clear(&data->lst_tok);
		data->exit_status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

void	clean_data(t_data *data)
{
	ft_lst_env_clear(&data->lst_env);
	data->lst_env = NULL;
	ft_lst_tok_clear(&data->lst_tok);
	data->lst_tok = NULL;
	ft_lst_exec_clear(&data->lst_exec);
	data->lst_exec = NULL;
	ft_free_array(data->env);
	data->env = NULL;
	free(data->pids);
	if (data->tmp_fd > 2)
		safe_close(&data->tmp_fd);
	data->pids = NULL;
}
