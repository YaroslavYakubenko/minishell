/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:07:58 by dyao              #+#    #+#             */
/*   Updated: 2024/09/08 12:52:09 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char )*s1 - (unsigned char)*s2);
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

char	*ft_output_final(char *final, char *str)
{
	int		k;
	int		j;

	k = 0;
	while (str[k] != '=' && str[k])
	{
		final[k] = str[k];
		k++;
	}
	if (str[k] == '=')
	{
		final[k] = str[k];
		k++;
		j = k;
		final[j++] = '"';
		while (str[k])
			final[j++] = str[k++];
		final[j++] = '"';
		final[j] = '\0';
	}
	else
		final[k] = '\0';
	return (final);
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

void		ft_export(char	**argv, char **evnp)
{
	char		**store;
	static char	*record[255];
	int 		argc;
	static int	i;

	if (argc == 2 && ft_strcmp(argv[1], "export") == 0)
	{
		store = ft_sort_the_evnp(evnp);
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
