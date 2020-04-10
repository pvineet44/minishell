/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:58:42 by vparekh           #+#    #+#             */
/*   Updated: 2020/04/10 18:54:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				get_args(t_minishell_meta *ms, char *line, int index)
{
	int		i;
	int		quote_bit;
	int		j;

	if ((i = check_endline(line, ms, &j, &quote_bit)) < 0)
		return (-i);
	while (line && line[ms->n = i] && line[i] != 26)
	{
		if (ft_isredir(line[i]) && quote_bit % 2 == 0)
			break ;
		if (ft_isspace(line[i]) && (quote_bit % 2 == 0))
		{
			(ms->arg == NULL) ? ms->arg = ft_strdup("") : (void)ms->arg;
			ms->piped_cmds->args1[index][j++] = ft_strdup(ms->arg);
			while (ft_free(&ms->arg) && line[i] != '\0' && ft_isspace(line[i]))
				i++;
			continue;
		}
		if (line[i] == 24 && (quote_bit = quote_bit + (0 * ++i) + 1))
			continue;
		else
			ms->arg = ft_stradd(ms->arg, line[i]);
		i++;
	}
	return (return_value(ms, index, j, line));
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
		exit(1);
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
