/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:48:14 by user42            #+#    #+#             */
/*   Updated: 2020/04/10 18:52:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_endline(char *line, t_minishell_meta *ms, int *j, int *q)
{
	int i;

	*j = 0;
	*q = 0;
	i = 0;
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	if ((line[i] == '\0' || line[i] == 26 || ft_isredir(line[i]))\
	&& (ms->no_args = 1))
		return (-i);
	return (i);
}

int			return_value(t_minishell_meta *ms, int index, int j, char *line)
{
	int i;

	i = ms->n;
	if (ms->arg)
		ms->piped_cmds->args1[index][j++] = ft_strdup(ms->arg);
	else if (line[i - 1] == 24 && line[i - 2] == 24)
		ms->piped_cmds->args1[index][j++] = ft_strdup("");
	ft_free(&ms->arg);
	ms->piped_cmds->args1[index][j] = 0;
	return (i);
}

char		*return_line(char *line, t_minishell_meta *ms)
{
	ft_free(&line);
	line = ft_strdup(ms->arg);
	ft_free(&ms->arg);
	return (line);
}

int			free_on_multiline(t_minishell_meta *ms)
{
	if (ms->arg != NULL && (ms->process_bit = -1))
		ft_free(&ms->arg);
	ft_putstr("Multiline commands not supported\n");
	errno = 1;
	return (1);
}

int			add_to_line(char *line, int i, t_minishell_meta *ms)
{
	ms->arg = ft_stradd(ms->arg, 24);
	i = parse_quotes(line, i, ms);
	if (i == 0 && ft_free(&line) && free_on_multiline(ms))
		return (-1);
	ms->arg = ft_stradd(ms->arg, 24);
	return (i);
}
