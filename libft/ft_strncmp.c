/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:13:04 by yyakuben          #+#    #+#             */
/*   Updated: 2023/12/07 16:20:40 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 1;
	if (n == 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && count++ < n)
	{
		s1++;
		s2++;
	}
	return ((unsigned char )*s1 - (unsigned char)*s2);
}
