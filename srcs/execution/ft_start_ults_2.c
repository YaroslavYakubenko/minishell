/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_ults_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:24:45 by dyao              #+#    #+#             */
/*   Updated: 2024/10/06 18:41:08 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_pipes(t_cmd *temp, int **pipes, int *i_for_pipe)
{
	if (temp->after_pipe)
	{
		close(pipes[*i_for_pipe][0]);
		(*i_for_pipe)++;
	}
	if (temp->before_pipe)
	{
		close(pipes[*i_for_pipe][1]);
	}
}

void	ft_free_double_pointer_int(int **pointer)
{
	int	i;

	i = 0;
	if (!pointer)
		return ;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free(pointer);
}

void	ft_check_and_execute(char **cmd, char **envp)
{
	if (ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "unset") == 0
		|| ft_strcmp(cmd[0], "env") == 0)
		ft_export(cmd, envp);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		;
	else
		ft_execute(cmd, envp);
}
