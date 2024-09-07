/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:21:03 by dyao              #+#    #+#             */
/*   Updated: 2024/09/07 18:23:23 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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