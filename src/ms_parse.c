/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:58:42 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/06 16:26:32 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void					pre_parse(t_minishell_meta *ms, char *line)
{
	char sc;

	sc = ';';
	if (ft_strchr(line, sc) != NULL)
	{
		ms->args = ft_split(line, sc);
		ms->args_loaded= 1;
	}
	else
	{
		ms->args = (char **)malloc(1 * sizeof(char*));
		ms->args[0] = ft_strdup(line);
		ms->args[1] = NULL;
	}
}

void					parse(t_minishell_meta *ms, char *line)
{
	if (ft_strcmp(line, CMD_EXIT) == 0)
		ms->cmd = 'x';
	if (ft_strcmp(line, CMD_PWD) == 0)
		ms->cmd = 'p';
	if (ft_strcmp(line, CMD_ENV) == 0)
		ms->cmd = 'n';
	return ;
}
