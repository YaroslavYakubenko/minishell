/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:21:03 by dyao              #+#    #+#             */
/*   Updated: 2024/10/03 18:36:39 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_pid(pid_t *pid_first)
{
	int	status;
	int	i;
	int	j;

	j = 0;
	while (pid_first[j])
	{
		i = waitpid(pid_first[j], &status, 0);
		if (i == -1)
		{
			perror("Error waiting for process\n");
			exit (EXIT_FAILURE);
		}
		if (!(WIFEXITED(status)))
			perror("process did not exit normally!\n");
		j++;
	}
}

int	ft_check_absolute_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	ft_execute(char **cmd, char **envp)
{
	char	*path;
	int		mark;

	if (!ft_check_absolute_path(cmd[0]))
		path = ft_get_evn(envp, "PATH", cmd[0]);
	else
		path = ft_strdup(cmd[0]);
	mark = execve(path, cmd, envp);
	if (mark)
	{
		perror(strerror(errno));
		free (path);
		exit (EXIT_FAILURE);
	}
}
