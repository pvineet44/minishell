/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:33:37 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 17:12:55 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void		check_opt_bit(t_minishell_meta *ms)
{
	if (ft_strncmp("-n ", ms->arg, 3) == 0)
		ms->opt_bit = 1;
	if (ft_strncmp("-n", ms->arg, 2) == 0 && ms->arg[3] == '\0')
		ms->opt_bit = 1;
}

void				ms_echo(t_minishell_meta *ms)
{
	int		i;
	int		c;
	char	*buff;

	buff = NULL;
	if (ms->arg_bit != 1)
	{
		write(1, "\n", 1);
		return ;
	}
	c = 0;
	i = 0;
	buff = ms->arg;
	check_opt_bit(ms);
	if (ms->opt_bit == 1)
		buff = &ms->arg[3];
	i = ft_strlen(buff);
	while (buff && ft_isspace(buff[i - 1]))
		i--;
	write(1, buff, i);
	if (ms->opt_bit != 1)
		write(1, "\n", 1);
}
