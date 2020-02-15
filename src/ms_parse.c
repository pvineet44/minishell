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

static int			line_param(t_minishell_meta *ms, char *line)
{
	int		i;

	i = 0;
	while (line && ft_isspace(line[i]))
		i++;
	while (line && !ft_isredir(line[i]) && line[i] != '\0')
	{
		if (line[i] == '\\')
		{
			ms->arg = ft_stradd(ms->arg, line[i+1]);
			i = i + 2;
			continue;
		}
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = parse_quotes(line, i, ms);
			if (i == 0)
			{
				if (ms->arg != NULL && (ms->process_bit = -1))
					free(ms->arg);
				ft_putstr("Multiline commands not supported\n");
				return (-1);
			}
		}
		else if (line[i] == '$')
			i = substitute_value(line, i, ms);
		else
			ms->arg = ft_stradd(ms->arg, line[i]);
		i++;
	}
	return (i);
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
	if (!(pipe->files = (char**)malloc(sizeof(char*) + (length
	* sizeof(char*)))))
		return (NULL);
	return (pipe);
}

void			load_cmds_args(t_minishell_meta *ms, char **line_splits)
{
	int		i;
	int		arg_end;

	i = -1;
	while (line_splits[++i] != NULL && (ft_free(&ms->arg)))
	{
		ms->piped_cmds->cmds[i] = NULL;
		ms->piped_cmds->args[i] = NULL;
		ms->piped_cmds->cmds[i] = get_command(ms->piped_cmds->cmds[i],\
		line_splits[i], ms);
		arg_end = line_param(ms, &line_splits[i][ms->arg_start]);
		if (arg_end == -1 && (ms->multiline = 1))
			return;
		if (ms->arg == NULL)
	  		ms->arg = ft_strdup("");
		ms->piped_cmds->args[i] = ft_strdup(ms->arg);
		ms->piped_cmds->files[i] = get_file(ms->piped_cmds->files[i],\
		&line_splits[i][arg_end+ms->arg_start], ms);
	}
	ms->piped_cmds->cmds[i] = 0;
	ms->piped_cmds->args[i] = 0;
	ms->piped_cmds->files[i] = 0;
	ft_free(&ms->arg);
}

void			parse_piped_commands(t_minishell_meta *ms, char *line, char d)
{
	int i;
	char					**line_splits;
	t_piped_minishell_meta	*pipe;

	(void)ms;
	line_splits = NULL;
	pipe = NULL;
	i = 0;
	line_splits = ft_split(line, d);
	pipe = init_cmds(ft_strlen(line));
	ms->piped_cmds = pipe;
	load_cmds_args(ms, line_splits);
	// check_args(pipe->cmds);
	// exit(EXIT_SUCCESS);	
}

void			parse(t_minishell_meta *ms, char *line)
{
	char **line_splits;
	ms->piped_cmds = init_cmds(ft_strlen(line));
	if (ft_strchr(line, ';') != NULL)
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
	// check_args(ms->piped_cmds->files);
	// exit(EXIT_SUCCESS);
}
