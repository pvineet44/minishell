/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:27:26 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 11:22:22 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					free_all(t_minishell_meta *ms, char *line)
{
	int i;

	i = 0;
	char **cmds;
	char **args;

	cmds = ms->piped_cmds->cmds;
	args = ms->piped_cmds->args;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	ft_free(&line);
	free(cmds);
	cmds = 0;
	free(args);
	args = 0;
	free(ms->piped_cmds);
	ms->piped_cmds = 0;
}

void			free_tab(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = 0;
		i++;
	}
	free(args);
	args = 0;
}