/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:16:45 by dyao              #+#    #+#             */
/*   Updated: 2024/09/09 14:43:36 by dyao             ###   ########.fr       */
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

	input = readline(">");
	while (input != NULL)
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
		input = readline(">");
	}
	printf("%s", output_str);
	free (output_str);
	ft_pipe();
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
