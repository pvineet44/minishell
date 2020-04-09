/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ce_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 12:55:04 by vparekh           #+#    #+#             */
/*   Updated: 2020/03/02 11:17:55 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				no_path_set(char *cmd)
{
	no_file_or_directory(cmd, 0);
	errno = 127;
	return (-1);
}

int				check_and_execute_path(t_minishell_meta *ms, int i)
{
	char			*path;
	int				j;
	struct stat		buffer;
	char			*tmp_cmd;

	j = 0;
	if (ms->path == 0)
		return (no_path_set(ms->piped_cmds->cmds[i]));
	while (ms->path[j] != NULL)
	{
		tmp_cmd = ft_strjoin(ms->path[j], "/");
		path = ft_strjoin(tmp_cmd, ms->piped_cmds->cmds[i]);
		if (lstat(path, &buffer) == 0)
		{
			ms_execute(path, ms->piped_cmds->args1[i], ms->env);
			ft_free(&tmp_cmd);
			ft_free(&path);
			return (1);
		}
		ft_free(&path);
		ft_free(&tmp_cmd);
		j++;
	}
	return (0);
}

void			check_args3(char ***args)
{
	int i;

	i = 0;
	while (args[i])
	{
		check_args(args[i]);
		i++;
	}
}

int				ft_tablen(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}
