/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:04:44 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/22 18:18:45 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						ft_isexecutable(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		return (1);
	return (0);
}

void					process(t_minishell_meta *ms, char *line)
{
	int		i;

	i = 0;
	while (ms->piped_cmds->cmds[i] != NULL)
	{
		if (ft_strcmp(ms->piped_cmds->files[i], "") != 0)
			handle_fd(ms->piped_cmds->files[i], ms, i);
		if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_EXIT) == 0)
			ms_exit(ms, line);
		else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_PWD) == 0)
			ms_pwd();
		else if (ft_isexecutable(ms->piped_cmds->cmds[i]))
			ms_execute(ms->piped_cmds->cmds[i], ms->piped_cmds->args[i],\
			ms->env);
		else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_CD) == 0)
			ms_cd(ms->piped_cmds->args[i]);
		else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_ENV) == 0)
			ms_env(ms->env);
		else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_ECHO) == 0)
			ms_echo(ms->piped_cmds->args[i]);
		else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_UNSET) == 0)
			ms_unset(ms->env, ms->piped_cmds->args[i]);
		else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_EXPORT) == 0)
			ms_export(ms->env, ms->piped_cmds->args[i]);
		if (ft_strcmp(ms->piped_cmds->files[i], "") != 0)
			unset_fd(ms);
		i++;
	}
}
