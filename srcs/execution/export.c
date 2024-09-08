/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:07:58 by dyao              #+#    #+#             */
/*   Updated: 2024/09/08 16:04:33 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_output_single_evnp(char *evnp)
{
	int		i;
	char	*output_evnp;
	char	*new_evnp;

	i = 0;
	while (evnp[i] && evnp[i] != '=')
		i++;
	new_evnp = malloc((i + 1) * sizeof(char));
	i = 0;
	while (evnp[i] && evnp[i] != '=')
		new_evnp[i] = evnp[i++];
	new_evnp[i] = '\0';
	output_evnp = getenv(new_evnp);
	new_evnp = ft_strjoin(new_evnp, "=");
	new_evnp = ft_strjoin(new_evnp, output_evnp);
	return (new_evnp);
}

char	**ft_renew_evnp(char **evnp)
{
	int		i;
	int		j;
	char	**new_evnp;
	char	*single_evnp;
	char	*output_evnp;

	while (evnp[i])
		i++;
	new_evnp = malloc(i * sizeof(char *));
	i = 0;
	j = 0;
	while (evnp[i])
	{
		single_evnp = ft_output_single_evnp(evnp[i]);
		new_evnp[i] = single_evnp;
		i++;
	}
	return (new_evnp);
}

char	**ft_sort_the_evnp(char **evnp)
{
	char	**store;
	char	*temp;
	int		i;

	i = 0;
	store = evnp;
	while (store[i + 1])
	{
		if (ft_strcmp(store[i], store[i + 1]) > 0)
		{
			temp = store[i];
			store[i] = store[i + 1];
			store[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (store);
}

void	ft_print_double_pointer(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void	ft_export(char	**argv, char **evnp)
{
	char		**store;
	static char	*record[255];
	int			argc;
	static int	i;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 2 && ft_strcmp(argv[1], "export") == 0)
	{
		store = ft_renew_evnp(evnp);
		store = ft_sort_the_evnp(store);
		ft_print_double_pointer(store);
		ft_print_double_pointer(record);
	}
	else if (argc > 2 && ft_strcmp(argv[1], "export") == 0)
		ft_record(argv[2], record[i++]);
	else if (argc == 2 && ft_strcmp(argv[1], "unset") == 0)
		printf("\n");
	else if (argc > 2 && ft_strcmp(argv[1], "unset") == 0)
		ft_unset(record, argv[2]);
}
