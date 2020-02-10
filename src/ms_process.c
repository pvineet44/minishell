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
		if (ft_strcmp(cmds[i], CMD_EXIT) == 0)
			ms_exit1(ms);
		if (ft_strcmp(cmds[i], CMD_PWD) == 0)
			ms_pwd();
		if (ft_strcmp(cmds[i], CMD_ENV) == 0)
			ms_env(ms->env);
		
		i++;
	}
}
