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

static int pre_process_cmd(char **command, int i, char *line, int *quote_bit)
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
char						*get_command(char *line,
t_minishell_meta *ms)
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

t_piped_minishell_meta		*init_cmds(int length)
{
	t_piped_minishell_meta	*pipe;
	int						i;

	i = 0;
	if (!(pipe = malloc(sizeof(t_piped_minishell_meta))))
		return (NULL);
	if (!(pipe->cmds = (char**)malloc(sizeof(char*) + (length
	* sizeof(char*)))))
		return (NULL);
	if (!(pipe->args1 = (char***)malloc(sizeof(char**) + (length
	* sizeof(char**)))))
		return (NULL);
	while (i <= (length))
	{
		if (!(pipe->args1[i] = (char**)malloc(sizeof(char*) + (length
		* sizeof(char*)))))
			return (NULL);
		pipe->args1[i][0] = 0;
		i++;
	}
	pipe->length = length + 1;
	i = 0;
	if (!(pipe->files1 = (char***)malloc(sizeof(char**) + (length
	* sizeof(char**)))))
		return (NULL);
	while (i <= (length))
	{
		if (!(pipe->files1[i] = (char**)malloc(sizeof(char*) + (length
		* sizeof(char*)))))
			return (NULL);
		pipe->files1[i][0] = 0;
		i++;
	}
	i = 0;
	if (!(pipe->redir = (char***)malloc(sizeof(char**) + (length
	* sizeof(char**)))))
		return (NULL);
	while (i <= (length))
	{
		if (!(pipe->redir[i] = (char**)malloc(sizeof(char*) + (length
		* sizeof(char*)))))
			return (NULL);
		pipe->redir[i][0] = 0;
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

void				get_files(char *line, t_minishell_meta *ms, int index)
{
	int		i;
	int		quote_bit;
	int		j;

	j = 0;
	i = 0;
	quote_bit = 0;
	while (line[i] != '\0' && ft_isalpha(line[i]))
		i++;
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0' || !ft_isredir(line[i]))
		return ;
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
			ft_free(&ms->arg);
		while (line[i] != '\0' && ft_isspace(line[i]))
			i++;
		while (line[i] && line[i] != 26)
		{
			if (line[i] == 24 && (quote_bit = quote_bit + 1))
			{
				i++;
				continue;
			}
			if ((ft_isspace(line[i]) || ft_isredir(line[i])) && (quote_bit % 2))
			{
				ms->arg = ft_stradd(ms->arg, line[i]);
				i++;
				continue;
			}
			if (!ft_isspace(line[i]) && (!ft_isredir(line[i])))
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
