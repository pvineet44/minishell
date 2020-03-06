/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:52:37 by mashar            #+#    #+#             */
/*   Updated: 2020/02/15 17:24:18 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char						*get_command(char *line,
t_minishell_meta *ms)
{
	int		i;
	char	*command;
	int		quote_bit;

	i = 0;
	quote_bit = 0;
	command = NULL;
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	if (line[i] == 24 && (quote_bit = 1))
		i++;
	while (line[i] && ft_isspace(line[i]))
	{
		command = ft_stradd(command, line[i]);
		i++;
	}
	while (line[i] && (!ft_isspace(line[i]) || quote_bit % 2) && line[i] != '\0' &&\
	line[i] != 26)
	{
		if (ft_isredir(line[i]) && !(quote_bit % 2))
			break;
		if (line[i] != 24)
			command = ft_stradd(command, line[i]);
		else
			quote_bit++;
		i++;
	}
	ms->arg_start = i;
	return (command);
}

t_piped_minishell_meta		*init_cmds(int length)
{
	t_piped_minishell_meta	*pipe;
	int i;

	i = 0;
	if (!(pipe = malloc(sizeof(t_piped_minishell_meta))))
		return (NULL);
	if (!(pipe->cmds = (char**)malloc(sizeof(char*) + (length
	* sizeof(char*)))))
		return (NULL);
	if (!(pipe->args1 = (char***)malloc(sizeof(char**) + (length / 2
	* sizeof(char**)))))
		return (NULL);
	while (i  <= (length / 2))
	{
		if (!(pipe->args1[i] = (char**)malloc(sizeof(char*) + (length
		* sizeof(char*)))))
			return (NULL);
		i++;
	}
	i = 0;
	if (!(pipe->files1 = (char***)malloc(sizeof(char**) + (length / 2
	* sizeof(char**)))))
		return (NULL);
	while (i  <= (length / 2))
	{
		if (!(pipe->files1[i] = (char**)malloc(sizeof(char*) + (length
		* sizeof(char*)))))
			return (NULL);
		i++;
	}
	i = 0;
	if (!(pipe->redir = (char***)malloc(sizeof(char**) + (length / 2
	* sizeof(char**)))))
		return (NULL);
	while (i  <= (length / 2))
	{
		if (!(pipe->redir[i] = (char**)malloc(sizeof(char*) + (length
		* sizeof(char*)))))
			return (NULL);
		i++;
	}
	if (!(pipe->pipe = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	pipe->pipe = ft_memset(pipe->pipe, 'x', length);
	pipe->pipe[length] = '\0';
	return (pipe);
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

char						*get_file(char *file,
char *line, t_minishell_meta *ms)
{
	int		i;
	int		quote_bit;

	i = 0;
	quote_bit = 0;
	(void)ms;
	
	file = NULL;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == 24 && (quote_bit = 1))
		i++;
	while (line[i] && !ft_isredir(line[i]))
		i++;
	if (line[i] == '\0' || (line[i] != '<' && line[i] != '>'))
		return (ft_strdup(""));
	while (line[i] != '\0' && line[i] != 26)
	{
		file = ft_stradd(file, line[i]);
		i++;
	}
	return (file);
}

void				get_files(char *line, t_minishell_meta *ms, int index)
{
	int		i;
	int		quote_bit;
	int		j;

	j = 0;
	i = 0;
	quote_bit = 0;
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	while (line[i] && line[i] != 26)
	{
		while (line[i] && ft_isredir(line[i]))
		{
			ms->arg = ft_stradd(ms->arg, line[i]);
			i++;
		}
		if (ms->arg)
		{
			ms->piped_cmds->redir[index][j] = ft_strdup(ms->arg);
			ft_free(&ms->arg);
		}
		else
		{
			ms->piped_cmds->redir[index][j] = ft_strdup("");
			ft_free(&ms->arg);
		}
		while (line[i] != '\0' && ft_isspace(line[i]))
			i++;
		while (line[i]  && line[i] != 26)
		{
			if (line[i] == 24 && quote_bit++)
			{
				i++;
				continue;
			}
			if ((ft_isspace(line[i]) || ft_isredir(line[i])) && (quote_bit%2))
			{
				ms->arg = ft_stradd(ms->arg, line[i]);
				i++;
				continue;
			}
			if (!ft_isspace(line[i])&& (!ft_isredir(line[i])))
			{
				ms->arg = ft_stradd(ms->arg, line[i]);
				i++;
				continue ;
			}
			break ;

		}
		if (ms->arg)
		{
			ms->piped_cmds->files1[index][j++] = ft_strdup(ms->arg);
			ft_free(&ms->arg);
		}
	}
	if (ms->arg)
	{
		ms->piped_cmds->files1[index][j++] = ft_strdup(ms->arg);
		ft_free(&ms->arg);
	}
	ms->piped_cmds->redir[index][j] = 0;
	ms->piped_cmds->files1[index][j] = 0;
}