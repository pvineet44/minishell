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
	(void)sig;
	signal(SIGINT, sig_int_handler);
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
