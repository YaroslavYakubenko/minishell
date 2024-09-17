/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:16:45 by dyao              #+#    #+#             */
/*   Updated: 2024/09/17 20:05:37 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_next_redirection(int i, t_token **tokens)
{
	while (tokens[i])
	{
		if (tokens[i]->type == 0)
			i++;
		else
			return (tokens[i]->type);
	}
	return (0);
}

void	ft_input(t_token **tokens, int i, char **envp)
{
	int		fd;
	int		mark;
	char	**cmd;

	fd = open(tokens[++i]->token, O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	mark = ft_check_next_redirection(i, tokens);
	if (mark == 1)
	{
		while (tokens[i]->type != 1)
			i++;
		ft_pipe(tokens, i, envp);
	}
	else if (mark == 3)
	{
		while (tokens[i]->type != 3)
			i++;
		ft_output(tokens, i);
	}
	else if (mark == 4)
	{
		while (tokens[i]->type != 4)
			i++;
		ft_append(tokens, i);
	}
	else if (mark == 0)
	{
		i++;
		if (tokens[i])
		{
			cmd = ft_creat_cmd(tokens, i);
			ft_check_and_execute_v2(cmd, envp);
		}
		else
		{
			i = 0;
			cmd = ft_creat_cmd(tokens, i);
			ft_check_and_execute_v2(cmd, envp);
		}
	}
	close(fd);
}

void	ft_output(t_token **tokens, int i)
{
	int	fd;

	fd = open(tokens[++i]->token, O_RDWR | O_CREAT | O_TRUNC, 0777);
	dup2(STDOUT_FILENO, fd);
	close(fd);
}

void	ft_append(t_token **tokens, int i)
{
	int	fd;

	fd = open(tokens[++i]->token, O_RDWR | O_CREAT | O_APPEND, 0777);
	dup2(STDOUT_FILENO, fd);
	close(fd);
}

void	ft_heredocs(t_token **tokens, int i, char **envp)
{
	char	*input;
	char	*output_str;

	while(*envp);
	input = readline(">");
	while (input != NULL)
	{
		if (ft_strcmp(input, tokens[++i]->token) == 0)
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
	// ft_pipe();
}

void	ft_pipe(t_token **tokens, int i, char **envp)
{
	pid_t	pid;
	pid_t	pid2;
	int		j;
	int		fd_pipe[2];
	char	**cmd;

	pid2 = fork();
	if (pid2 == 0)
	{
		pipe(fd_pipe);
		pid = fork();
		if (pid == 0)
		{
			i--;
			while (tokens[i]->type == 0 && i > 0)
				i--;
			j = i;
			while (tokens[i] && tokens[i]->type == 0)
				i++;
			cmd = malloc((i - j + 1) * sizeof(char *));
			i = j;
			j = 0;
			while (tokens[i] && tokens[i]->type == 0)
				cmd[j++] = ft_strdup(tokens[i++]->token);
			cmd[j] = NULL;
			dup2(fd_pipe[1], STDOUT_FILENO);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			ft_check_and_execute(cmd, envp);
			free(cmd);
		}
		else
		{
			j = ++i;
			while (tokens[i] && tokens[i]->type == 0)
				i++;
			cmd = malloc((i - j + 1) * sizeof(char *));
			i = j;
			j = 0;
			while (tokens[i] && tokens[i]->type == 0)
				cmd[j++] = ft_strdup(tokens[i++]->token);
			cmd[j] = NULL;
			dup2(fd_pipe[0], STDIN_FILENO);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			ft_check_and_execute(cmd, envp);
			free(cmd);
		}
	}
	else
		ft_wait_pid(pid2);
}
