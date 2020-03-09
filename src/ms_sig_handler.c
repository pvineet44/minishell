/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_sig_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:54:48 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 12:54:49 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_handler(int sig)
{
	if (sig == SIGINT)
	{
		errno = 1;
		ft_putstr(" \b\b \b\b ");
		ft_putstr("\n");
		write(STDERR_FILENO, SHELL_BANNER, 15);
		signal(SIGINT, sig_int_handler);
	}
}

void	proc_signal_handler(int sig)
{
	errno = 130;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		signal(SIGINT, proc_signal_handler);
	}
}

void	proc_sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		signal(SIGINT, proc_sigquit_handler);
	}
}

void	sig_quit_handler(int sig)
{
	(void)sig;
	ft_putstr(" \b\b \b\b \b");
	signal(SIGQUIT, sig_quit_handler);
}

int		get_exit_status(t_minishell_meta *ms)
{
	char	*errno_str;
	int		x;

	errno_str = ft_itoa(errno);
	x = 0;
	while (errno_str[x] != '\0')
	{
		ms->arg = ft_stradd(ms->arg, errno_str[x]);
		x++;
	}
	return (0);
}
