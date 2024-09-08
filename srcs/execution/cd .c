/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd .c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:13:13 by dyao              #+#    #+#             */
/*   Updated: 2024/09/08 12:45:57 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *dest_dir)
{
	DIR	*dir;
	int	i;

	dir = opendir(dest_dir);
	if (dir == NULL)
	{
		i = 0;
		while (strerror(errno)[i])
			i++;
		write(2, strerror(errno), i);
	}
}