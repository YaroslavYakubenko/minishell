/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:13:13 by dyao              #+#    #+#             */
/*   Updated: 2024/09/11 14:42:25 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *dest_dir)
{
	int	dir;
	int	i;

printf("test1\n");
	dir = chdir(dest_dir);
	if (dir == -1)
	{
		i = 0;
		while (strerror(errno)[i])
			i++;
		write(2, strerror(errno), i);
	}
printf("test2\n");
}
