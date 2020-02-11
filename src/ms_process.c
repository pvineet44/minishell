/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:04:44 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/09 17:27:31 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					process(t_minishell_meta *ms, char *line)
{
	int		i;
	char	**cmds;
	char	**args;

	i = 0;
	cmds = ms->piped_cmds->cmds;
	args = ms->piped_cmds->args;
	while (ms->piped_cmds->cmds[i] != NULL)
	{
		if (ms->redir == '>')
			set_out_fd(args[i], &ms->out_fd);
		if (ft_strcmp(cmds[i], CMD_EXIT) == 0)
			ms_exit(ms, line);
		else if (ft_strcmp(cmds[i], CMD_PWD) == 0)
			ms_pwd();
		else if (ft_strcmp(cmds[i], CMD_ENV) == 0)
			ms_env(ms->env);
		else if (ft_strcmp(cmds[i], CMD_ECHO) == 0)
			ms_echo(args[i]);
		else if (ft_strcmp(cmds[i], CMD_UNSET) == 0)
			ms_unset(ms->env, args[i]);
		else if (ft_strcmp(cmds[i], CMD_EXPORT) == 0)
			ms_export(ms->env, args[i]);
		if (ms->redir == '>')
			unset_fd(&ms->out_fd);
		i++;
	}
}
