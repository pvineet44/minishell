/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:52:37 by mashar            #+#    #+#             */
/*   Updated: 2020/04/10 18:47:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int					pre_process_cmd(char **command, int i, char *line,\
int *quote_bit)
{
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	if (line[i] == 24 && (*quote_bit = 1))
		i++;
	while (line[i] && ft_isspace(line[i]))
	{
		*command = ft_stradd(*command, line[i]);
		i++;
	}
	return (i);
}

char						*get_command(char *line, t_minishell_meta *ms)
{
	int		i;
	char	*command;
	int		quote_bit;

	i = 0;
	quote_bit = 0;
	command = NULL;
	i = pre_process_cmd(&command, i, line, &quote_bit);
	while (line[i] && (!ft_isspace(line[i]) || quote_bit % 2)\
	&& line[i] != '\0' && line[i] != 26)
	{
		if (ft_isredir(line[i]) && !(quote_bit % 2))
			break ;
		if (line[i] != 24)
			command = ft_stradd(command, line[i]);
		else
			quote_bit++;
		i++;
	}
	if (command == NULL)
		command = ft_strdup("");
	ms->arg_start = i;
	return (command);
}

char						*get_redir(char *redir,
char *line, t_minishell_meta *ms)
{
	int i;

	i = 0;
	redir = NULL;
	if (line[i] == '\0')
		return (ft_strdup(""));
	while (ft_isredir(line[i]) && line[i] != '\0')
	{
		redir = ft_stradd(redir, line[i]);
		i++;
	}
	ms->arg_start += i;
	return (redir);
}

int							get_file_name(char *line, int i,\
int *quote_bit, char **str)
{
	while (line[i] && line[i] != 26)
	{
		if (line[i] == 24 && (*quote_bit = *quote_bit + 1))
		{
			i++;
			continue;
		}
		if ((ft_isspace(line[i]) || ft_isredir(line[i])) && (*quote_bit % 2))
		{
			str[0] = ft_stradd(str[0], line[i]);
			i++;
			continue;
		}
		if (!ft_isspace(line[i]) && (!ft_isredir(line[i])))
		{
			str[0] = ft_stradd(str[0], line[i]);
			i++;
			continue ;
		}
		return (i);
	}
	return (i);
}

void						get_files(char *line,\
t_minishell_meta *ms, int index)
{
	int		i;
	int		quote_bit;
	int		j;

	i = 0;
	quote_bit = 0;
	while ((j = 0) && line[i] != '\0' && ft_isalpha(line[i]))
		i++;
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0' || !ft_isredir(line[i]))
		return ;
	while (line[i] && line[i] != 26)
	{
		while (line[i] && ft_isredir(line[i]))
			ms->arg = ft_stradd(ms->arg, line[i++]);
		j = add_ms_arg(ms, index, j, 0);
		while (line[i] != '\0' && ft_isspace(line[i]))
			i++;
		i = get_file_name(line, i, &quote_bit, &ms->arg);
		j = add_ms_arg(ms, index, j, 1);
	}
	j = add_ms_arg(ms, index, j, 1);
	ms->piped_cmds->redir[index][j] = 0;
	ms->piped_cmds->files1[index][j] = 0;
}
