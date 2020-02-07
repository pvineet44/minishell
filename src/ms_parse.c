/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:58:42 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 15:00:09 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<stdio.h>
#include "minishell.h"
#include <stdio.h>

void					pre_parse(t_minishell_meta *ms, char *line)
{
	char sc;

	sc = ';';
	if (ft_strchr(line, sc) != NULL)
		ms->args = ft_split(line, sc);
	else
	{
		ms->args = (char **)malloc(2 * sizeof(char*));
		ms->args[0] = ft_strdup(line);
		ms->args[1] = 0;
	}
}

void line_param(t_minishell_meta *ms, char *line)
{
	int		i;
	int		quote_cnt;
	char	*arg;

	quote_cnt = 1;
	i = 0;
	arg = NULL;
	while(line && ft_isspace(line[i]))
		i++;
	while (line && line[i] != '\0')
	{
		if (line[i] != '\'')
			arg=ft_stradd(arg,line[i]);
		else
			quote_cnt *= -1;
		i++;
	}
	if (arg == NULL)
		return ;
	if (quote_cnt < 0)
		ft_putstr("multiline comments not supported\n");
	else
		ms->arg = ft_strdup(arg);
	free(arg);
	ft_putstr(ms->arg);
}

void					command_not_found(char *command)
{
		write(1, "minishell: ", 11);
		write(1, command, ft_strlen(command));
		write(1, COMMAND_NOT_FOUND, 20);
}

char						*get_command(char *command, char *line, t_minishell_meta *ms)
{

	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while(line[i] && ft_isspace(line[i]))
		i++;
	k = i;
	while(!ft_isspace(line[i]) && line[i++] != '\0')
		j++;
	if(!(command = (char*)malloc(sizeof(char)* (j+1))))
		ms_exit(ms, line);
	j = 0;
	while(!ft_isspace(line[k]) && line[k] != '\0')
		command[j++] = line[k++];
	command[j] = '\0';
	ms->arg_start = k;
	return command;
}

void					parse(t_minishell_meta *ms, char *line)
{
	char *command;

	ms->opt_bit = 0;
	command = NULL;
	command = get_command(command, line, ms);
	if (ft_strcmp(command, CMD_EXIT) == 0)
		ms->cmd = 'x';
	else if (ft_strcmp(command, CMD_PWD) == 0)
		ms->cmd = 'p';
	else if (ft_strcmp(command, CMD_ENV) == 0)
		ms->cmd = 'n';
	else if (ft_strcmp(command, CMD_ECHO) == 0 && (ms->opt_bit = 1))
		ms->cmd = 'e';
	else
		command_not_found(command);
	if (ms->opt_bit == 1)
		line_param(ms, &line[ms->arg_start]);
	free(command);
	return;
}
