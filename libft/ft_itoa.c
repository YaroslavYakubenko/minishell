/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:27:40 by yyakuben          #+#    #+#             */
/*   Updated: 2023/11/30 09:05:34 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_create_num(size_t i, char *str, size_t len, unsigned long n)
{
	unsigned long	res;

	if (i < len && str + i && n)
	{
		res = n % 10;
		n /= 10;
		*(str + i) = res + '0';
		i++;
		ft_create_num(i, str, len, n);
	}
}

static size_t	ft_count_size(unsigned long n, size_t i)
{
	if (n)
	{
		n /= 10;
		i++;
		return (ft_count_size(n, i));
	}
	return (i);
}

static void	ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	ft_revert(char *str, size_t size, size_t sign)
{
	size_t	i;
	size_t	j;

	if (sign)
		*(str + size) = '-';
	size += sign;
	i = 0;
	j = size - 1;
	while (i < size / 2)
	{
		ft_swap(str + i, str + j);
		i++;
		j--;
	}
}

char	*ft_itoa(int n)
{
	unsigned long	num;
	size_t			size;
	int				sign;
	char			*str;

	sign = 0;
	size = 0;
	if (!n)
		return (ft_strdup("0"));
	if (n < 0)
	{
		num = (long)n * (-1);
		sign = 1;
	}
	else
		num = (unsigned long)n;
	size = ft_count_size(num, 0);
	str = malloc(size + 1 + sign);
	if (!str)
		return (NULL);
	ft_create_num(0, str, size, num);
	ft_revert(str, size, sign);
	*(str + size + sign) = '\0';
	return (str);
}
