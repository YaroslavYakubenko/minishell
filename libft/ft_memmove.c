/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:28:23 by yyakuben          #+#    #+#             */
/*   Updated: 2023/12/07 16:39:04 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*destination;
	int				i;

	if (src == dst)
		return (dst);
	source = (unsigned char *)src;
	destination = (unsigned char *)dst;
	i = n - 1;
	if (source < destination)
	{
		while (i >= 0)
		{
			destination[i] = source[i];
			i--;
		}
	}
	while (i >= 0)
	{
		*destination = *source;
		i--;
		source++;
		destination++;
	}
	return (dst);
}
