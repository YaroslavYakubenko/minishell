/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:07:55 by yyakuben          #+#    #+#             */
/*   Updated: 2024/08/07 18:08:09 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc.h"

bool	ft_alloc_init(void)
{
	t_allocs	*lst;

	lst = ft_calloc(1, sizeof(t_allocs));
	if (lst == NULL)
		return (false);
	ft_allocs(lst);
	return (true);
}
