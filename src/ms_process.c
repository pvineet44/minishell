/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:04:44 by vparekh           #+#    #+#             */
/*   Updated: 2020/03/02 11:50:52 by vparekh          ###   ########.fr       */
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

int						process_builtin(t_minishell_meta *ms, int i, char *line)
{
	int stat;

	stat = 0;
	if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_EXIT) == 0 && (stat = 1))
		ms_exit(ms, line);
	else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_PWD) == 0 && (stat = 1))
		ms_pwd();
	else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_CD) == 0 && (stat = 1))
		ms_cd(ms->piped_cmds->args[i], ms);
	else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_ENV) == 0 && (stat = 1))
		ms_env(ms->env);
	else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_ECHO) == 0 && (stat = 1))
		ms_echo(ms->piped_cmds->args[i]);
	else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_UNSET) == 0 && (stat = 1))
		ms_unset(ms->env, ms->piped_cmds->args[i]);
	else if (ft_strcmp(ms->piped_cmds->cmds[i], CMD_EXPORT) == 0 && (stat = 1))
		ms_export(ms->env, ms->piped_cmds->args[i]);
	return (stat);
}

void					search_and_execute_path(t_minishell_meta *ms, int i)
{
	if (ft_strchr(ms->piped_cmds->cmds[i], '/') != NULL)
		ms_execute(ms->piped_cmds->cmds[i], ms->piped_cmds->args[i], ms->env);
	else if (check_and_execute_path(ms, i) != 1)
		command_not_found(ms, i);
}

void					process(t_minishell_meta *ms, char *line)
{
	int		i;
	int		in;

	i = 0;
	in = 0;
	while (ms->piped_cmds->cmds[i] != NULL)
	{
		if (ms->piped_cmds->pipe[i] == '|')
		{
			process_piped_cmd(ms, line, i, &in);
			i++;
			continue;
		}
		process_cmd(ms, line, i);
		i++;
	}
}
