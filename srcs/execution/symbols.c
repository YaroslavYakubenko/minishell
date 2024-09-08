/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:16:45 by dyao              #+#    #+#             */
/*   Updated: 2024/09/08 12:55:54 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_output(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_append(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0777);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_heredocs(char *end)
{
	char	*input;
	char	*output_str;

	while ((input = readline(">")) != NULL)
	{
		if (ft_strcmp(input, end) == 0)
		{
			free(input);
			break ;
		}
		if (!output_str)
			output_str = ft_strjoin(output_str, input);
		else
		{
			output_str = ft_strjoin(output_str, "\n");
			output_str = ft_strjoin(output_str, input);
		}
	}
	printf("%s", output_str);
	ft_pipe;
}

void	ft_pipe(void)
{
	pid_t	pid;
	int		fd_pipe[2];

	pipe(fd_pipe);
	dup2(fd_pipe[1], STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		dup2(fd_pipe[0], STDIN_FILENO);
}
