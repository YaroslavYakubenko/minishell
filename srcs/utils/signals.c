/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:28:20 by yyakuben          #+#    #+#             */
/*   Updated: 2024/09/30 17:50:52 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
	write(1, "\b\b  \b\b", 5);
}

void	eof_handler(int sig)
{
	(void)sig;
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}