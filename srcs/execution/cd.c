/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:13:13 by dyao              #+#    #+#             */
/*   Updated: 2024/09/26 16:22:30 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *dest_dir)
{
	int		dir;
	int		mark;
	char	new_dir[1024];
	char	*final_dir;

	if (!dest_dir)
	{
		dir = 0;
		mark = 0;
		getcwd(new_dir, sizeof(new_dir));
		while (new_dir[dir])
		{
			if (new_dir[dir] == '/')
				mark++;
			if (mark == 3)
				break ;
			dir++;
		}
		final_dir = ft_strndup(new_dir, dir);
		dir = chdir(final_dir);
		if (dir == -1)
			perror(strerror(errno));
		free(final_dir);
	}
	else
	{
		dir = chdir(dest_dir);
		if (dir == -1)
			perror(strerror(errno));
	}
}
