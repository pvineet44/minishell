/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:04:44 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 16:02:21 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					process(t_minishell_meta *ms, char *line)
{
	if (ms->cmd == 'x')
		ms_exit(ms, line);
	if (ms->cmd == 'p')
		ms_pwd(ms);
	if (ms->cmd == 'n')
		ms_env(ms);
	if (ms->cmd == 'e')
		ms_echo(ms);
	if (ms->arg_bit)
		free(ms->arg);
}

void					process1(t_minishell_meta *ms)
{
	int i;
	char **cmds;
	char **args;

	i = 0;
	cmds = ms->piped_cmds->cmds;
	args = ms->piped_cmds->args;
	while (ms->piped_cmds->cmds[i] != NULL)
	{
		if (ft_strcmp(cmds[i], CMD_PWD) == 0)
			ms_pwd1();
		i++;
	}
}
