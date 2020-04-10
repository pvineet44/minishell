/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 18:36:16 by user42            #+#    #+#             */
/*   Updated: 2020/04/10 19:19:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int							check_file_permission(char *path)
{
	struct stat file_stat;

	if (stat(path, &file_stat) >= 0 && ((file_stat.st_mode & S_IXUSR) == 0))
	{
		write_permission_denied(path);
		return (0);
	}
	return (1);
}

int							check_red_err(char *line, int i,\
t_minishell_meta *ms)
{
	if (line[i] == '\\')
	{
		if (line[i + 1] == '\0' && ft_free(&line) && free_on_multiline(ms))
			return (-1);
		ms->arg = ft_stradd(ms->arg, line[i + 1]);
		i++;
		return (i);
	}
	else if (line[i] == ';' && (line[i] = 25))
	{
		if (line[i + 1] == ';' && syntax_error(";;")\
		&& ft_free(&ms->arg) && ft_free(&line))
			return (-1);
	}
	else if (line[i] == '|')
	{
		if (line[i] == '|' && i == 0 && syntax_error("|") && ft_free(&line))
			return (-1);
		line[i] = 26;
	}
	ms->arg = ft_stradd(ms->arg, line[i]);
	return (i);
}

char						*refine_line(char *line, t_minishell_meta *ms)
{
	int		i;

	i = 0;
	while (i < ft_strlen(line))
	{
		if ((line[i] == '\'' || line[i] == '\"')\
		&& (i == 0 || line[i - 1] != '\\'))
		{
			if ((i = add_to_line(line, i, ms)) == -1)
				return (0);
		}
		else if (line[i] == '$')
			i = substitute_value(line, i, ms);
		else if (line[i] != '|' && ft_isredir(line[i]))
		{
			i = check_invalid_redir(line, i, ms);
			if (i == 0 && ft_free(&line))
				return (0);
			continue ;
		}
		else if ((i = check_red_err(line, i, ms)) == -1)
			return (0);
		i++;
	}
	return (return_line(line, ms));
}

char						***create_3d_array(int length)
{
	char	***array;
	int		i;

	i = 0;
	if (!(array = (char***)malloc(sizeof(char**) + length * sizeof(char**))))
		return (NULL);
	while (i <= length)
	{
		if (!(array[i] = (char**)malloc(sizeof(char*) * (length + 1))))
			return (NULL);
		array[i][0] = 0;
		i++;
	}
	return (array);
}

t_piped_minishell_meta		*init_cmds(int length)
{
	t_piped_minishell_meta	*pipe;

	if (!(pipe = malloc(sizeof(t_piped_minishell_meta))))
		return (NULL);
	if (!(pipe->cmds = (char**)malloc(sizeof(char*) + (length
	* sizeof(char*)))))
		return (NULL);
	pipe->length = length + 1;
	if (!(pipe->args1 = create_3d_array(length)))
		return (NULL);
	if (!(pipe->files1 = create_3d_array(length)))
		return (NULL);
	if (!(pipe->redir = create_3d_array(length)))
		return (NULL);
	if (!(pipe->pipe = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	pipe->pipe = ft_memset(pipe->pipe, 'x', length);
	pipe->pipe[length] = '\0';
	return (pipe);
}
