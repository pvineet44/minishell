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

void			free_tab_tab(char ***args)
{
	int i;

	i = 0;
	while (args[i] != 0)
	{
		free_tab(args[i]);
		i++;
	}
	if (args)
	{
		free(args);
		args = 0;
	}
}

void					free_all(t_minishell_meta *ms, char *line)
{
	int				i;

	i = 0;
	if (ms->piped_cmds!= 0)
	{
		free_tab(ms->piped_cmds->cmds);
		free_tab_tab(ms->piped_cmds->args1);
		free_tab_tab(ms->piped_cmds->files1);
		free_tab_tab(ms->piped_cmds->redir);
		ft_free(&ms->piped_cmds->pipe);
		free(ms->piped_cmds);
		ms->piped_cmds = 0;
	}
	ft_free(&line);
}

void					free_tab(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
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
