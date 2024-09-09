/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:25:08 by dyao              #+#    #+#             */
/*   Updated: 2024/09/09 14:37:31 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_build_in(char **cmd, char **envp)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd[1]);
	else if (ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "unset") == 0)
		ft_export(cmd, envp);
}
