/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:58:00 by yyakuben          #+#    #+#             */
/*   Updated: 2023/11/14 21:00:10 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int arg)
{
	if (arg >= 'A' && arg <= 'Z')
		return (arg + 32);
	return (arg);
}
