/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:54:41 by dyao              #+#    #+#             */
/*   Updated: 2024/09/18 18:51:50 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_and_execute(char **cmd, char **envp)
{
	if (ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "unset") == 0)
		ft_export(cmd, envp);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd[1]);
	else
		ft_execute(cmd, envp);
}

void	ft_check_and_execute_v2(char **cmd, char **envp)
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

char	**ft_creat_cmd(t_token **tokens, int i)
{
	int		j;
	char	**cmd;

	j = i;
	while (tokens[i] && tokens[i]->type == 0)
		i++;
	cmd = malloc((i - j + 1) * sizeof(char *));
	i = j;
	j = 0;
	while (tokens[i] && tokens[i]->type == 0)
		cmd[j++] = ft_strdup(tokens[i++]->token);
	cmd[j] = NULL;
	return (cmd);
}

void	ft_start(t_token **tokens, char **envp)
{
	int		i;
	int		mark;
	char	**cmd;

	i = 0;
	mark = 9;
	while (tokens[i])
	{
		if (tokens[i]->type == 5)
			mark = 5;
		else if (tokens[i]->type == 1)
			mark = 1;
		else if (tokens[i]->type == 2)
			mark = 2;
		else if (tokens[i]->type == 3)
			mark = 3;
		else if (tokens[i]->type == 4)
			mark = 4;
		else
			mark = 0;
		if (mark != 0)
			break ;
		else
			i++;
	}
	if (mark == 5)
		ft_heredocs(tokens, i, envp);
	else if (mark == 1)
		ft_pipe(tokens, i, envp);
	else if (mark == 2)
		ft_input(tokens, i, envp);
	else if (mark == 3)
		ft_output(tokens, i);
	else if (mark == 4)
		ft_append(tokens, i);
	else
	{
		mark = 0;
		i = 0;
		cmd = ft_creat_cmd(tokens, i);
		ft_check_and_execute_v2(cmd, envp);
	}
}
