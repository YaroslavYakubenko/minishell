/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ults_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:38:52 by dyao              #+#    #+#             */
/*   Updated: 2024/10/01 12:39:38 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_double_pointer(char **str)
{
	int	i;

	if (!str || !str[0])
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] != '_')
			printf("%s\n", str[i]);
		i++;
	}
}

void	ft_print_env(char **evnp)
{
	char	**store;

	store = ft_renew_evnp(evnp);
	ft_print_double_pointer(store);
	ft_read_and_print();
}
