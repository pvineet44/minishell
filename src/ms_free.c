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
	int				i;
	char			**cmds;
	char			**args;
	char			**files;

	i = 0;
	cmds = ms->piped_cmds->cmds;
	args = ms->piped_cmds->args;
	files = ms->piped_cmds->files;
	free_tab(cmds);
	free_tab(args);
	free_tab(files);
	ft_free(&line);
	ft_free(&ms->piped_cmds->pipe);
	if (ms->piped_cmds)
	{
		free(ms->piped_cmds);
		ms->piped_cmds = 0;
	}
}

void					free_tab(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		ft_free(&args[i]);
		args[i] = 0;
		i++;
	}
	if (args)
	{
		free(args);
		args = 0;
	}
}
