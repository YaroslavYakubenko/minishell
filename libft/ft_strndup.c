/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:37:07 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/02 15:51:22 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <string.h>

char *ft_strndup(const char *src, size_t n)
{
    size_t	len;
    char	*dest;

	len = ft_strnlen(src, n);
	dest = (char *)malloc(len + 1);
    if (!dest)
        return NULL;
    ft_memcpy(dest, src, len);
    dest[len] = '\0';
    return (dest);
}
