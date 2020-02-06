/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:58:42 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/05 16:43:33 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include "minishell.h"

char *line_param(t_minishell_meta *ms, char *line)
{
	int i;
	i = -1;
	(void)ms;
	char *test;
	test = NULL;
	while (line[++i] != '\0')
	{
		if (line[i] != '\'')
		{
			test=ft_stradd(test,line[i]);
		}
	}
	ft_putstr(test);
	return (0);
}

int					parse(t_minishell_meta *ms, char *line)
{	char *command;
	int i;
	int j;
	int k;
	char *param;
	
	i = 0;
	j = 0;
	k = 0;
	while(!ft_isalpha(line[i]))
		i++;
	k = i;
	while(ft_isalpha(line[i]) && line[i++] != '\0')
		j++;
	if(!(command = (char*)malloc(sizeof(char)* (j+1))))
		return 0;
	j = 0;
	while(ft_isalpha(line[k]) && line[k] != '\0')
		command[j++] = line[k++];
	command[j] = '\0';
	if (ft_strcmp(command, CMD_EXIT) == 0)
		ms->cmd = 'x';
	if (ft_strcmp(command, CMD_PWD) == 0)
		ms->cmd = 'p';
	if (ft_strcmp(command, CMD_ENV) == 0)
		ms->cmd = 'n';
	if (ms->cmd != 'x' && ms->cmd != 'p' && ms->cmd != 'n')
		param = line_param(ms, &line[k]);
	
	return 1;
}
