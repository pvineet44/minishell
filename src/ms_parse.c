/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:58:42 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 15:54:42 by vparekh          ###   ########.fr       */
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

int		parse_quotes(char *line, int i, t_minishell_meta *ms)
{
	int		quote_bit;
	char	quote;

	quote = line[i];
	quote_bit = line[i] == '\'' ? 1 : 0;/*zero for double quote, 1 for single quote*/
	i++;
	while((line[i] != '\0') && (line[i] != quote))
	{
		ms->arg = ft_stradd(ms->arg, line[i]);
		i++;
	}
	if (line[i] != quote)
		return (0);
	return i;
}

int		substitute_value(char *line, int i, t_minishell_meta *ms)
{
	(void)ms;
	(void)line;
	return i;
}

void line_param(t_minishell_meta *ms, char *line)
{
	int		i;

	i = 0;
	ms->arg = NULL;
	while(line && ft_isspace(line[i]))
		i++;
	while (line && line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = parse_quotes(line, i, ms);
			if (i == 0)
			{
				if (ms->arg != NULL && (ms->process_bit = -1))
					free(ms->arg);
				ft_putstr("Multiline comments not supported\n");
				return;
			}
		}
		else if (line[i] == '$')
			i = substitute_value(line, i, ms);
		else
			ms->arg = ft_stradd(ms->arg,line[i]);
		i++;
	}
	if (ms->arg == NULL)
		return ;
}

void			command_not_found(char *command)
{
		write(1, "minishell: ", 11);
		write(1, command, ft_strlen(command));
		write(1, COMMAND_NOT_FOUND, 20);
}

char			*get_command(char *command, char *line, t_minishell_meta *ms)
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

	ms->arg_bit = 0;
	command = NULL;
	command = get_command(command, line, ms);
	if (ft_strcmp(command, CMD_EXIT) == 0)
		ms->cmd = 'x';
	else if (ft_strcmp(command, CMD_PWD) == 0)
		ms->cmd = 'p';
	else if (ft_strcmp(command, CMD_ENV) == 0)
		ms->cmd = 'n';
	else if (ft_strcmp(command, CMD_ECHO) == 0 && (ms->arg_bit = 1))
		ms->cmd = 'e';
	else
		command_not_found(command);
	if (ms->arg_bit == 1)
		line_param(ms, &line[ms->arg_start]);
	free(command);
	return;
}
