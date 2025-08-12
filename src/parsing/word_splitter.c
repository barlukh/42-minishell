/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:43:54 by bgazur            #+#    #+#             */
/*   Updated: 2025/08/12 10:44:30 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	expansion_splitter(t_token *current, t_data *data)
// {
//     char    **arr;
//     size_t  i;
//     t_token *node;
//     t_token *prev;
//     t_token *next;

//     if (!current || !current->content)
//         return ;

//     if (ft_strchr(current->content, ' ') != NULL)
//     {
//         arr = ft_split(current->content, ' ');
//         if (!arr)
//             error_env_exp(data);

//         next = current->next;
// 		free(current->content);
//         current->content = ft_strdup(arr[0]);
//         if (!current->content)
//         {
//             ft_free_array(arr);
//             error_env_exp(data);
//         }

//         i = 1;
//         prev = current;
//         while (arr[i])
//         {
//             node = ft_lst_tok_new(arr[i]);
//             if (!node)
//             {
//                 ft_free_array(arr);
//                 error_env_exp(data);
//             }
//             prev->next = node;
//             prev = node;
//             i++;
//         }
//         prev->next = next;
//         ft_free_array(arr);
//     }
// }
