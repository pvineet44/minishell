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

char						*fetch_redir(char *line, int *i)
{
	char	*redir_seq;
	int		j;

	j = *i;
	redir_seq = NULL;
	redir_seq = ft_stradd(redir_seq, line[*i]);
	j++;
	if (line[j] == '>')
	{
		redir_seq = ft_stradd(redir_seq, line[j]);
		j++;
	}
	*i = j;
	return (redir_seq);
}

int							throw_newline_error(t_minishell_meta *ms)
{
	syntax_error("newline");
	ft_free(&ms->arg);
	return (0);
}

int							check_invalid_redir(char *line, int i,\
t_minishell_meta *ms)
{
	char *redir_seq;
	char *tmp;

	redir_seq = fetch_redir(line, &i);
	if (ms->arg == NULL)
		tmp = ft_strdup(redir_seq);
	else
		tmp = ft_strjoin(ms->arg, redir_seq);
	ft_free(&ms->arg);
	ms->arg = ft_strdup(tmp);
	ft_free(&tmp);
	ft_free(&redir_seq);
	if (line[i] == 0)
		return (throw_newline_error(ms));
	else if (ft_isredir(line[i]))
	{
		redir_seq = fetch_redir(line, &i);
		syntax_error(redir_seq);
		ft_free(&redir_seq);
		ft_free(&ms->arg);
		return (0);
	}
	ft_free(&redir_seq);
	return (i);
}
