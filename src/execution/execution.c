/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:25:47 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/13 17:55:01 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set pipes() generate pipes fd
// set fork() generate children
// dup2() Fds managment
// execve() Execution
//
void	execution(t_data *data)
{
	(void)data;
}

// execve(env_path, data->lst_tok: , data env);
//
// Idea of recycling pipes
// void	recycle_pipe(t_args *args)
// {
// 	if (args->index % 2 == 0)
// 	{
// 		close(args->pipes[0]);
// 		close(args->pipes[1]);
// 		pipe(args->pipes);
// 	}
// 	else
// 	{
// 		close(args->pipis[0]);
// 		close(args->pipis[1]);
// 		pipe(args->pipis);
// 	}
// }
