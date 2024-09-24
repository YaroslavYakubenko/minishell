/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:13:13 by dyao              #+#    #+#             */
/*   Updated: 2024/09/24 20:47:16 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *dest_dir)
{
	int	dir;

	dir = chdir(dest_dir);
	if (dir == -1)
		perror(strerror(errno));
	else
		fprintf(stderr, "Successfully changed directory to: %s\n", dest_dir);
}
