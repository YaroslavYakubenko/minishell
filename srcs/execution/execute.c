/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:21:03 by dyao              #+#    #+#             */
/*   Updated: 2024/09/10 19:33:34 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char **cmd, char **envp)
{
	char	*path;
	int		mark;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		path = ft_get_evn(envp, "PATH", cmd[0]);
		mark = execve(path, cmd, envp);
		if (mark)
		{
			perror(strerror(errno));
			free (path);
			exit (EXIT_FAILURE);
		}
	}
	waitpid(pid, 0, 0);
}
