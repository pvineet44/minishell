/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:58:42 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/09 17:10:36 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			pre_parse(t_minishell_meta *ms, char *line)
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

void			line_param(t_minishell_meta *ms, char *line)
{
	int		i;

	i = 0;
	while (line && ft_isspace(line[i]))
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
				return ;
			}
		}
		else if (line[i] == '$')
			i = substitute_value(line, i, ms);
		else
			ms->arg = ft_stradd(ms->arg, line[i]);
		i++;
	}
}

char			*get_command(char *command, char *line, t_minishell_meta *ms)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	k = i;
	while (!ft_isspace(line[i]) && line[i++] != '\0')
		j++;
	if (!(command = (char*)malloc(sizeof(char) * (j + 1))))
		ms_exit(ms, line);
	j = 0;
	while (!ft_isspace(line[k]) && line[k] != '\0')
		command[j++] = line[k++];
	command[j] = '\0';
	ms->arg_start = k;
	return (command);
}

void			parse_piped_commands(t_minishell_meta *ms, char *line)
{
	int i;
	char					**line_splits;
	t_piped_minishell_meta	*pipe;

	(void)ms;
	line_splits = NULL;
	pipe = NULL;
	i = 0;
	line_splits = ft_split(line, '|');
	if (!(pipe = malloc(sizeof(t_piped_minishell_meta))))
		return ;
	if (!(pipe->cmds = (char**)malloc(sizeof(char*) + (ft_strlen(line)
	* sizeof(char*)))))
		return ;
	if (!(pipe->args = (char**)malloc(sizeof(char*) + (ft_strlen(line)
	* sizeof(char*)))))
		return ;
	while (line_splits[i] != NULL)
	{
		pipe->cmds[i] = NULL;
		pipe->args[i] = NULL;
		pipe->cmds[i] = get_command(pipe->cmds[i], line_splits[i], ms);
		ms->cmd = '|';
		line_param(ms, &line_splits[i][ms->arg_start]);
		if (ms->arg == NULL)
			ms->arg = ft_strdup("");
		pipe->args[i] = ft_strdup(ms->arg);
		ft_free(&ms->arg);
		i++;
	}
	ms->piped_cmds = pipe;
	// check_args(pipe->args);
	// exit(EXIT_SUCCESS);
	
}

void			parse(t_minishell_meta *ms, char *line)
{
	char *command;

	command = NULL;
	if (ft_strchr(line, '|') != NULL)
	{
		parse_piped_commands(ms, line);
		process1(ms);
		return ;
	}
	command = get_command(command, line, ms);
	if (ft_strcmp(command, CMD_EXIT) == 0)
		ms->cmd = 'x';
	else if (ft_strcmp(command, CMD_PWD) == 0)
		ms->cmd = 'p';
	else if (ft_strcmp(command, CMD_ENV) == 0)
		ms->cmd = 'n';
	else if (ft_strcmp(command, CMD_UNSET) == 0 && (ms->arg_bit = 1))
		ms->cmd = 'u';
	else if (ft_strcmp(command, CMD_EXPORT) == 0 && (ms->arg_bit = 1))
		ms->cmd = 't';
	else if (ft_strcmp(command, CMD_ECHO) == 0 && (ms->arg_bit = 1))
		ms->cmd = 'e';
	else
		command_not_found(command);
	if (ms->arg_bit == 1)
		line_param(ms, &line[ms->arg_start]);
	if (ms->arg == NULL)
		ms->arg_bit = 0;
	free(command);
	return ;
}
