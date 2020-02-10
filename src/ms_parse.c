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

t_piped_minishell_meta			*init_cmds(int length)
{
	t_piped_minishell_meta	*pipe;

	if (!(pipe = malloc(sizeof(t_piped_minishell_meta))))
		return (NULL);
	if (!(pipe->cmds = (char**)malloc(sizeof(char*) + (length
	* sizeof(char*)))))
		return (NULL);
	if (!(pipe->args = (char**)malloc(sizeof(char*) + (length
	* sizeof(char*)))))
		return (NULL);
	return (pipe);
}

void			load_cmds_args(t_minishell_meta *ms, char **line_splits)
{
	char	**cmds;
	char	**args;
	int		i;

	i = 0;
	cmds = ms->piped_cmds->cmds;
	args = ms->piped_cmds->args;
	while (line_splits[i] != NULL)
	{
		cmds[i] = NULL;
		args[i] = NULL;
		cmds[i] = get_command(cmds[i], line_splits[i], ms);
		line_param(ms, &line_splits[i][ms->arg_start]);
		if (ms->arg == NULL)
			ms->arg = ft_strdup("");
		args[i] = ft_strdup(ms->arg);
		ft_free(&ms->arg);
		i++;
	}
	cmds[i] = 0;
	args[i] = 0;
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
	pipe = init_cmds(ft_strlen(line));
	ms->piped_cmds = pipe;
	load_cmds_args(ms, line_splits);
	// check_args(pipe->args);
	// exit(EXIT_SUCCESS);	
}

void			parse(t_minishell_meta *ms, char *line)
{
	char **line_splits;
	ms->piped_cmds = init_cmds(ft_strlen(line));
	if (ft_strchr(line, '|') != NULL)
	{
		parse_piped_commands(ms, line);
		return ;
	}
	else if (ft_strchr(line, ';') != NULL)
	{
		line_splits = ft_split(line, ';');
	}
	else
	{
		line_splits = (char **)malloc(2 * sizeof(char*));
		line_splits[0] = ft_strdup(line);
		line_splits[1] = NULL;
	}
	load_cmds_args(ms, line_splits);
	free_tab(line_splits);
	// check_args(ms->piped_cmds->cmds);
	// exit(EXIT_SUCCESS);
}
