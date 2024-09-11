/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:54:41 by dyao              #+#    #+#             */
/*   Updated: 2024/09/11 16:15:58 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_and_execute(char **cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "unset") == 0)
			ft_export(cmd, envp);
		else if (ft_strcmp(cmd[0], "cd") == 0)
			ft_cd(cmd[1]);
		else
			ft_execute(cmd, envp);
	}
	else if (pid > 0)
		ft_wait_pid(pid);
}

int	ft_go_to_symbols(t_token **tokens, int i)
{
	if (tokens[i]->type == 5)
		i++;
	else if (tokens[i]->type == 1)
		ft_pipe();
	else if (tokens[i]->type == 2)
		ft_input(tokens[++i]->token);
	else if (tokens[i]->type == 3)
		ft_output(tokens[++i]->token);
	else if (tokens[i]->type == 4)
		ft_append(tokens[++i]->token);
	return (++i);
}

void	ft_start(t_token **tokens, char **envp)
{
	int		i;
	int		j;
	char	**cmd;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == 5)
			ft_heredocs(tokens[++i]->token);
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == 0)
		{
			j = i;
			while (tokens[i] && tokens[i]->type == 0)
				i++;
			cmd = malloc((i - j + 1) * sizeof(char *));
			i = j;
			j = 0;
			while (tokens[i] && tokens[i]->type == 0)
				cmd[j++] = ft_strdup(tokens[i++]->token);
			cmd[j] = NULL;
			ft_check_and_execute(cmd, envp);
		}
		else if (tokens[i]->type <= 5 && tokens[i]->type >= 1)
			i = ft_go_to_symbols(tokens, i);
	}
}
