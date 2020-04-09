/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:58:42 by vparekh           #+#    #+#             */
/*   Updated: 2020/03/02 11:44:55 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				free_on_multiline(t_minishell_meta *ms)
{
	if (ms->arg != NULL && (ms->process_bit = -1))
		ft_free(&ms->arg);
	ft_putstr("Multiline commands not supported\n");
	errno = 1;
	return ;
}

static int			get_args(t_minishell_meta *ms, char *line, int index)
{
	int		i;
	int		quote_bit;
	int		j;

	j = 0;
	i = 0;
	quote_bit = 0;
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	if ((line[i] == '\0' || line[i] == 26 || ft_isredir(line[i])) && (ms->no_args = 1))
		return (i);
	while (line && line[i] != '\0' && line[i] != 26 && !ft_isredir(line[i]))
	{
		if (ft_isspace(line[i]) && (quote_bit % 2 == 0))
		{
			if (ms->arg == NULL)
				ms->arg = ft_strdup("");
			ms->piped_cmds->args1[index][j++] = ft_strdup(ms->arg);
			ft_free(&ms->arg);
			while (line[i] != '\0' && ft_isspace(line[i]))
				i++;
			continue;
		}
		if (line[i] == 24 && (quote_bit = quote_bit + 1))
		{
			i++;
			continue;
		}
		else
			ms->arg = ft_stradd(ms->arg, line[i]);
		i++;
	}
	if (ms->arg)
		ms->piped_cmds->args1[index][j++] = ft_strdup(ms->arg);
	else if (line[i - 1] == 24 && line[i - 2] == 24)
		ms->piped_cmds->args1[index][j++] = ft_strdup("");
	ft_free(&ms->arg);
	ms->piped_cmds->args1[index][j] = 0;
	return (i);
}

int						parse_piped_commands(t_minishell_meta *ms,
char *line, int j)
{
	int	freq;
	int	start;
	int	arg_end;

	start = 0;
	freq = get_frequency(line, 26);
	while (freq-- >= 0 && ft_free(&ms->arg))
	{
		ms->piped_cmds->cmds[j] = get_command(&line[start], ms);
		arg_end = get_args(ms, &line[start + ms->arg_start], j) - 1
		+ start + ms->arg_start;
		get_files(&line[arg_end], ms, j);
		ms->piped_cmds->pipe[j++] = '|';
		while (line[arg_end] != '\0' && line[arg_end] != 26)
			arg_end++;
		start = arg_end + 1;
	}
	return (j);
}

void					load_cmds_args(t_minishell_meta *ms, char **line_splits)
{
	int		i;
	int		arg_end;
	int		j;

	i = -1;
	j = 0;
	while (line_splits[++i] != NULL && (ft_free(&ms->arg)))
	{
		if (ft_strchr(line_splits[i], 26))
		{
			j = parse_piped_commands(ms, line_splits[i], j);
			continue;
		}
		ms->piped_cmds->cmds[j] = get_command(line_splits[i], ms);
		arg_end = get_args(ms, &line_splits[i][ms->arg_start], j);
		get_files(&line_splits[i][arg_end + ms->arg_start], ms, j);
		j++;
	}
	terminate_tabs(ms, j);
}

char					*refine_line(char *line, t_minishell_meta *ms)
{
	int		i;
	int		len;

	i = 0;
	ms->arg = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if ((line[i] == '\'' || line[i] == '\"')\
		&& (i == 0 || line[i - 1] != '\\'))
		{
			ms->arg = ft_stradd(ms->arg, 24);
			i = parse_quotes(line, i, ms);
			if (i == 0)
			{
				ft_free(&line);
				free_on_multiline(ms);
				return (0);
			}
			ms->arg = ft_stradd(ms->arg, 24);
		}
		else if (line[i] == '$')
			i = substitute_value(line, i, ms);
		else if (line[i] != '|' && ft_isredir(line[i]))
		{
			i = check_invalid_redir(line, i, ms);
			if (i == 0)
			{
				ft_free(&line);
				return (0);
			}
			continue ;
		}
		else
		{
			if (line[i] == '\\')
			{
				if (line[i + 1] == '\0')
				{
					free_on_multiline(ms);
					return (0);
				}
				ms->arg = ft_stradd(ms->arg, line[i + 1]);
				i = i + 2;
				continue;
			}
			else if (line[i] == ';')
			{
				if (line[i + 1] == ';')
				{
					syntax_error(";;");
					return (0);
				}
				line[i] = 25;
			}
			else if (line[i] == '|')
			{
				if (line[i] == '|' && i == 0)
				{
					syntax_error("|");
					return (0);
				}
				line[i] = 26;
			}
			ms->arg = ft_stradd(ms->arg, line[i]);
		}
		i++;
	}
	ft_free(&line);
	line = ft_strdup(ms->arg);
	ft_free(&ms->arg);
	return (line);
}

char					*parse(t_minishell_meta *ms, char *line)
{
	char	**line_splits;

	if (check_line(line) && (ms->multiline = 1))
		return (line);
	line = refine_line(line, ms);
	if (((line == NULL) && (ms->multiline = 1)))
		return (line);
	ms->piped_cmds = init_cmds(ft_strlen(line));
	if (ms->piped_cmds == NULL)
	{
		//Exit the program
	}
	if (ft_strchr(line, 25) != NULL || ft_strchr(line, 26) != NULL)
		line_splits = ft_split(line, 25);
	else
	{
		line_splits = (char **)malloc(2 * sizeof(char*));
		line_splits[0] = ft_strdup(line);
		line_splits[1] = NULL;
	}
	load_cmds_args(ms, line_splits);
	free_tab(line_splits);
	return (line);
}
