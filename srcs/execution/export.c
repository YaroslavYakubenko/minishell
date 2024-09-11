/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:07:58 by dyao              #+#    #+#             */
/*   Updated: 2024/09/11 14:23:50 by dyao             ###   ########.fr       */
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
	{
		new_evnp[i] = evnp[i];
		i++;
	}
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

	i = 0;
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
	new_evnp[i] = NULL;
	return (new_evnp);
}

char	**ft_sort_the_evnp(char **store)
{
	char	*temp;
	int		i;

	i = 0;
	while (store[i + 1] != NULL)
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

void	ft_export(char	**argv, char **evnp)
{
	char		**store;
	static char	*record[255];
	int			argc;
	static int	i;

	argc = 0;
	if (!record[0])
		ft_put_null(record);
	while (argv[argc])
		argc++;
	if (argc == 1 && ft_strcmp(argv[0], "export") == 0)
	{
		store = ft_renew_evnp(evnp);
		store = ft_sort_the_evnp(store);
		ft_print_double_pointer(store);
		ft_print_double_pointer(record);
	}
	else if (argc > 1 && ft_strcmp(argv[0], "export") == 0)
		record[i++] = ft_record(argv[1]);
	else if (argc == 1 && ft_strcmp(argv[0], "unset") == 0)
		printf("unset: not enough arguments\n");
	else if (argc > 1 && ft_strcmp(argv[0], "unset") == 0)
		i = ft_unset(record, argv[1], i);
}
