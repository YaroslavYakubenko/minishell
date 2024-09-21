/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:21:03 by dyao              #+#    #+#             */
/*   Updated: 2024/09/22 00:48:21 by dyao             ###   ########.fr       */
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

fprintf(stderr, "\n\nTEST FOR CMD: %s\n\n", cmd[0]);
	path = ft_get_evn(envp, "PATH", cmd[0]);
	fprintf(stderr, "\n\nHERE PATH %s, the first of cmd is : %s, and the second of the cmd is: %s, the first line of the envp is: %s\n", path, cmd[0], cmd[1], envp[0]);
	
int	j;
j = 0;
while (cmd[j])
{
	fprintf(stderr, "\nthis is %d cmd:%s\n", j, cmd[j]);
	j++;
}

	
	mark = execve(path, cmd, envp);
	if (mark)
	{
		perror(strerror(errno));
		free (path);
		exit (EXIT_FAILURE);
	}
}
