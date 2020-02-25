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

char						*get_command(char *command, char *line,
t_minishell_meta *ms)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] != '\0' && ft_isspace(line[i]))
		i++;
	k = i;
	while (!ft_isspace(line[i])  && !ft_isredir(line[i]) && line[i++] != '\0')
		j++;
	if (!(command = (char*)malloc(sizeof(char) * (j + 1))))
		ms_exit(ms, line);
	j = 0;
	while (!ft_isspace(line[k]) && line[k] != '\0'  && !ft_isredir(line[k]))
		command[j++] = line[k++];
	command[j] = '\0';
	ms->arg_start = k;
	return (command);
}

t_piped_minishell_meta		*init_cmds(int length)
{
	t_piped_minishell_meta	*pipe;

	if (!(pipe = malloc(sizeof(t_piped_minishell_meta))))
		return (NULL);
	if (!(pipe->cmds = (char**)malloc(sizeof(char*) + (length
	* sizeof(char*)))))
		return (NULL);
	if (!(pipe->args = (char**)malloc(sizeof(char*) + (length
	* sizeof(char*)))))
		return (NULL);
	if (!(pipe->files = (char**)malloc(sizeof(char*) + (length
	* sizeof(char*)))))
		return (NULL);
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

	i = 0;
	(void)ms;
	file = NULL;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (ft_strdup(""));
	while (line[i] != '\0')
	{
		file = ft_stradd(file, line[i]);
		i++;
	}
	return (file);
}
