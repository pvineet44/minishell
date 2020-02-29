/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_input_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 12:51:18 by mashar            #+#    #+#             */
/*   Updated: 2020/02/22 12:51:21 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char						*replace_semi(char *line, int i, char quote,\
t_minishell_meta *ms)
{
	while (line[i] != quote && line[i] != '\0')
		i++;
	ms->end_quote = i;
	if (line[i] == '\0')
		return (0);
	return (line);
}

char						*parse_input_line(char *line, t_minishell_meta *ms)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ';' && line[i - 1] != '\\')
			line[i] = 25;
		if (line[i] == '|' && line[i - 1] != '\\')
			line[i] = 26;
		if (line[i] == '\'' || line[i] == '\"')
		{
			line = replace_semi(line, (i + 1), line[i], ms);
			i = ms->end_quote;
			if (line == NULL && (ms->multiline = 1))
				return (0);
		}
		i++;
	}
	return (line);
}

int							get_frequency(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
