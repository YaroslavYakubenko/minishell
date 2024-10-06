/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:06:49 by dyao              #+#    #+#             */
/*   Updated: 2024/10/06 19:21:50 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmd *cmd)
{
	int	i;

	unlink("index");
	if (cmd->args[1])
	{
		i = ft_atoi(cmd->args[1]);
		ft_free_nods(cmd);
		exit(i);
	}
	ft_free_nods(cmd);
	exit(EXIT_SUCCESS);
}
