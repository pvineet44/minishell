/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:58:42 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/15 17:25:31 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_on_multiline(t_minishell_meta *ms)
{
	if (ms->arg != NULL && (ms->process_bit = -1))
		ft_free(&ms->arg);
	ft_putstr("Multiline commands not supported\n");
	return ;
}

static int		line_param(t_minishell_meta *ms, char *line)
{
	int		i;

	i = 0;
	while (line && ft_isspace(line[i]))
		i++;
	while (line && !ft_isredir(line[i]) && line[i] != '\0')
	{
		if (line[i] == '\\')
			i++;
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = parse_quotes(line, i, ms);
			if (i == 0)
			{
				free_on_multiline(ms);
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


int			parse_piped_commands(t_minishell_meta *ms,
char *line, int j)
{
	int freq;
	int start;
	int arg_end;

	arg_end = 0;
	start = 0;
	freq = get_frequency(line, '|');
	while (freq >= 0 && ft_free(&ms->arg))
	{
		ms->piped_cmds->cmds[j] = get_command(ms->piped_cmds->cmds[j],\
		&line[start], ms);
		arg_end = line_param(ms, &line[start + ms->arg_start]) - 1 + start + ms->arg_start;
		if (arg_end == -1 && (ms->multiline = 1))
			return (-99);
		if (ms->arg == NULL)
			ms->arg = ft_strdup("");
		ms->piped_cmds->args[j] = ft_strdup(ms->arg);
		ms->piped_cmds->pipe[j] = '|';
		ms->piped_cmds->files[j] = get_file(ms->piped_cmds->files[j],\
		&line[arg_end], ms);
		freq--;
		j++;
		while(line[arg_end] != '\0' && line[arg_end] != '|')
			arg_end++;
		start = arg_end + 1;
		//ft_putnbr_fd(start, 1);
	}
	return (j);
}

void			load_cmds_args(t_minishell_meta *ms, char **line_splits)
{
	int		i;
	int		arg_end;
	int		j;

	i = -1;
	j = 0;
	while (line_splits[++i] != NULL && (ft_free(&ms->arg)))
	{
		ms->piped_cmds->cmds[j] = NULL;
		ms->piped_cmds->args[j] = NULL;
		if (ft_strchr(line_splits[i], '|'))
		{
			j = parse_piped_commands(ms, line_splits[i], j);
			continue;
		}
		ms->piped_cmds->cmds[j] = get_command(ms->piped_cmds->cmds[j],\
		line_splits[i], ms);
		arg_end = line_param(ms, &line_splits[i][ms->arg_start]);
		if (arg_end == -1 && (ms->multiline = 1))
			return ;
		if (ms->arg == NULL)
			ms->arg = ft_strdup("");
		ms->piped_cmds->args[j] = ft_strdup(ms->arg);
		ms->piped_cmds->files[j] = get_file(ms->piped_cmds->files[j],\
		&line_splits[i][arg_end + ms->arg_start], ms);
		j++;
	}
	ms->piped_cmds->cmds[j] = 0;
	ms->piped_cmds->args[j] = 0;
	ms->piped_cmds->files[j] = 0;
	ft_free(&ms->arg);
}

void			parse(t_minishell_meta *ms, char *line)
{
	int		i;
	char	**line_splits;

	i = 0;
	ms->piped_cmds = init_cmds(ft_strlen(line));
	if (ft_strchr(line, ';') != NULL)
	{
		if ((line = parse_input_line(line, ms)) == NULL)
			return ;
		line_splits = ft_split(line, 25);
	}
	else
	{
		line_splits = (char **)malloc(2 * sizeof(char*));
		line_splits[0] = ft_strdup(line);
		line_splits[1] = NULL;
	}
	load_cmds_args(ms, line_splits);
	free_tab(line_splits);
	// check_args(ms->path);
	check_args(ms->piped_cmds->cmds);
	check_args(ms->piped_cmds->args);
	check_args(ms->piped_cmds->files);
	ft_putstr_fd(ms->piped_cmds->pipe, 1);
	exit(EXIT_SUCCESS);
}
