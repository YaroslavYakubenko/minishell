/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_own.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:49:48 by dyao              #+#    #+#             */
/*   Updated: 2024/09/11 15:24:41 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_find_path(char *env_path, char *search_string)
{
	int	index;

	index = 0;
	if (env_path == NULL || search_string == NULL)
		return (NULL);
	while (search_string[index])
	{
		if (env_path[index] == search_string[index])
			index++;
		else
			return (NULL);
	}
	return (env_path + 5);
}

static char	*ft_return_path(char **envp, char *a)
{
	int		i;
	char	*path;

	if (!envp || !a)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		path = ft_find_path(envp[i], a);
		if (path != NULL)
			return (path);
		i++;
	}
	return (NULL);
}

static char	*ft_output_cmd(char *path, char *cmd)
{
	char	**a_path;
	char	*tempcmd;
	char	*finalcmd;
	int		i;

	i = 0;
	a_path = ft_split(path, ':');
	while (a_path[i])
	{
		tempcmd = ft_strjoin(a_path[i], "/");
		finalcmd = ft_strjoin(tempcmd, cmd);
		if (access(finalcmd, F_OK) == 0)
		{
			free (tempcmd);
			return (finalcmd);
		}
		free (tempcmd);
		free (finalcmd);
		i++;
	}
	i = -1;
	while (a_path[++i])
		free(a_path[i]);
	free(a_path);
	return (NULL);
}

char	*ft_get_evn(char **envp, char *keyword, char *cmd)
{
	char	*path;
	char	*temp;

	if (!envp || !keyword || !cmd)
		return (NULL);
	path = ft_return_path(envp, keyword);
	if (!path)
		return (NULL);
	temp = ft_output_cmd(path, cmd);
	if (temp == NULL)
	{
		write(2, "shell: command not found: ", 27);
		write(2, cmd, sizeof(cmd));
		write(2, "\n", 1);
		exit (EXIT_FAILURE);
	}
	return (temp);
}
