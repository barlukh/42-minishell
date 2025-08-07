/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:17:04 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/07 13:39:34 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_available_id(char **temp_name, size_t *i, t_data *data);
static void	create_temp_file(char *temp_name, int *fd, t_data *data);
static bool	get_user_input(int *fd, t_token *current);
static int	heredoc_event_hook(void);

bool	create_heredoc_temps(t_data *data)
{
	char	*temp_name;
	int		fd;
	size_t	i;
	t_token	*current;

	fd = 0;
	i = 0;
	current = data->lst_tok;
	while (current)
	{
		if (current->type == TOK_HERE_QTD || current->type == TOK_HERE_UNQTD)
		{
			find_available_id(&temp_name, &i, data);
			create_temp_file(temp_name, &fd, data);
			if (get_user_input(&fd, current) != SUCCESS)
			{
				ft_lst_tok_clear(&data->lst_tok);
				return (FAILURE);
			}
			i++;
		}
		current = current->next;
	}
	return (SUCCESS);
}

// Finds the next available id number for heredoc file.
static void	find_available_id(char **temp_name, size_t *i, t_data *data)
{
	char	*id;

	while (true)
	{
		id = ft_itoa(*i);
		if (!id)
			error_heredoc_mem(data);
		*temp_name = ft_strjoin(TEMP, id);
		free(id);
		id = NULL;
		if (!*temp_name)
			error_heredoc_mem(data);
		if (access(*temp_name, F_OK) == 0)
		{
			free(*temp_name);
			(*i)++;
		}
		else
			break ;
	}
}

// Creates a new heredoc file.
static void	create_temp_file(char *temp_name, int *fd, t_data *data)
{
	*fd = open(temp_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	free(temp_name);
	temp_name = NULL;
	if (*fd == -1)
		error_heredoc_file(data);
}

// Asks user for an input and writes it into the heredoc file.
static bool	get_user_input(int *fd, t_token *current)
{
	char	*input;

	input = NULL;
	signals_heredoc();
	while (true)
	{
		rl_event_hook = heredoc_event_hook;
		input = readline("> ");
		if (g_signal == 130)
		{
			free(input);
			return (FAILURE);
		}
		if (!input)
		{
			ft_putendl_fd(ERR_MSG_EOF, STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(input, current->content) == 0)
			break ;
		write(*fd, input, ft_strlen(input));
		write(*fd, "\n", 1);
	}
	free(input);
	return (SUCCESS);
}

// Function to call periodically when readline is waiting for terminal input.
static int	heredoc_event_hook(void)
{
	if (g_signal == 130)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}
