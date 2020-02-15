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
	char **files;

	cmds = ms->piped_cmds->cmds;
	args = ms->piped_cmds->args;
	files = ms->piped_cmds->files;
	while (cmds[i])
	{
		ft_free(&cmds[i]);
		i++;
	}
	i = 0;
	while (args[i])
	{
		ft_free(&args[i]);
		i++;
	}
	i = 0;
	while (files[i])
	{
		ft_free(&files[i]);
		i++;
	}
	ft_free(&line);
	free(cmds);
	cmds = 0;
	free(args);
	args = 0;
	free(files);
	files = 0;
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