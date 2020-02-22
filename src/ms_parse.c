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
			return ;
		if (ms->arg == NULL)
			ms->arg = ft_strdup("");
		ms->piped_cmds->args[i] = ft_strdup(ms->arg);
		ms->piped_cmds->files[i] = get_file(ms->piped_cmds->files[i],\
		&line_splits[i][arg_end + ms->arg_start], ms);
	}
	ms->piped_cmds->cmds[i] = 0;
	ms->piped_cmds->args[i] = 0;
	ms->piped_cmds->files[i] = 0;
	ft_free(&ms->arg);
}

void			parse_piped_commands(t_minishell_meta *ms,
char *line, char d)
{
	char					**line_splits;
	t_piped_minishell_meta	*pipe;

	(void)ms;
	line_splits = NULL;
	pipe = NULL;
	line_splits = ft_split(line, d);
	pipe = init_cmds(ft_strlen(line));
	ms->piped_cmds = pipe;
	load_cmds_args(ms, line_splits);
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
	// check_args(ms->piped_cmds->files);
	// exit(EXIT_SUCCESS);
}
