/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:27:51 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/17 11:05:33 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// Outputs the character ’c’ to the specified file descriptor.
// File descriptors are int assossiated with an open file or resource

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
