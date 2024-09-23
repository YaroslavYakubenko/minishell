/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:21:03 by dyao              #+#    #+#             */
/*   Updated: 2024/09/23 15:31:36 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_pid(pid_t pid_first, int j)
{
	int	status;
	int	i;

	i = waitpid(pid_first, &status, 0);
	if (i == -1)
	{
		perror("Error waiting for ");
		write(2, &j, 1);
		perror(" process\n");
		exit (EXIT_FAILURE);
	}
	if (!(WIFEXITED(status)))
	{
		write(2, &j, 1);
		perror(" process did not exit normally!\n");
	}
}

void	ft_execute(char **cmd, char **envp)
{
	char	*path;
	int		mark;

	path = ft_get_evn(envp, "PATH", cmd[0]);
	mark = execve(path, cmd, envp);
	if (mark)
	{
		perror(strerror(errno));
		free (path);
		exit (EXIT_FAILURE);
	}
}
