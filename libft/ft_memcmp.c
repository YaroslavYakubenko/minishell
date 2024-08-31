/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:26:30 by yyakuben          #+#    #+#             */
/*   Updated: 2023/12/06 17:26:24 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (((const unsigned char *)s1)[i]
		== ((const unsigned char *)s2)[i]))
		i++;
	if (i == n)
		return (0);
	return (((const unsigned char *)s1)[i] - ((const unsigned char *)s2)[i]);
}
