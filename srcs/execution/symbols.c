/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:16:45 by dyao              #+#    #+#             */
/*   Updated: 2024/09/24 20:48:23 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_heredoc(char *str)
{
	pid_t	pid;
	int		fd_pipe[2];

	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[1]);
		close(fd_pipe[0]);
		printf("%s", str);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		ft_wait_pid(pid, 0);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		// print_from_fd(STDIN_FILENO);
	}
}

void	ft_input(char *file_name)
{
	int		fd;

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
	char	*output_str = NULL;
	int		i;

	i = 0;
	input = readline("heredoc>");
	while (input != NULL)
	{
		if (ft_strcmp(input, end) == 0)
		{
			free(input);
			break ;
		}
		if (i++ == 0)
			output_str = ft_strdup(input);
		else
		{
			output_str = ft_strjoin(output_str, "\n");
			output_str = ft_strjoin(output_str, input);
		}
		input = readline("heredoc>");
	}
	output_str = ft_strjoin(output_str, "\n");
	ft_redir_heredoc(output_str);
	free (output_str);
}

