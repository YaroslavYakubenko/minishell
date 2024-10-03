/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:16:45 by dyao              #+#    #+#             */
/*   Updated: 2024/10/03 18:34:22 by dyao             ###   ########.fr       */
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
		waitpid(pid, NULL, 0);
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
}

char	*ft_deal_input(char *input, char *output_str)
{
	if (!output_str)
		output_str = ft_strdup(input);
	else
	{
		output_str = ft_strjoin_1(output_str, "\n");
		output_str = ft_strjoin_1(output_str, input);
	}
	return (output_str);
}

void	ft_heredocs(char *end)
{
	char	*input;
	char	*output_str;

	output_str = NULL;
	input = readline("heredoc>");
	while (input != NULL)
	{
		if (ft_strcmp(input, end) == 0)
		{
			free(input);
			break ;
		}
		output_str = ft_deal_input(input, output_str);
		free(input);
		input = readline("heredoc>");
	}
	output_str = ft_strjoin_1(output_str, "\n");
	ft_redir_heredoc(output_str);
	free (output_str);
}
