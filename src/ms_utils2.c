/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:28:53 by vparekh           #+#    #+#             */
/*   Updated: 2020/04/10 11:28:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				terminate_tabs(t_minishell_meta *ms, int j)
{
	ms->piped_cmds->cmds[j] = 0;
	ft_free(&ms->arg);
}

void				process_cmd(t_minishell_meta *ms, char *line, int i)
{
	if (ms->piped_cmds->files1[i][0] != 0)
	{
		handle_fd(ms, i);
	}
	if (ms->process_bit >= 0 && process_builtin(ms, i, line) == 0)
	{
		search_and_execute_path(ms, i);
	}
	if ((ms->piped_cmds->files1[i][0] != 0) && (ms->multiline != -99))
	{
		unset_fd(ms);
	}
}

void				process_piped_cmd(t_minishell_meta *ms, char *line,
int i, int *in)
{
	static	pid_t	pid;
	int				stat;

	if (!ms->piped_cmds->pipe[i + 1] || (ms->piped_cmds->pipe[i + 1] != '|'))
	{
		if ((pid = fork()) == 0)
		{
			if (*in != 0)
				dup2(*in, 0);
			process_cmd(ms, line, i);
			exit(errno);
		}
		waitpid(pid, &stat, 0);
		errno = stat / 255;
	}
	else
	{
		pipe(ms->mypipe);
		spawn_proc(ms, line, *in, i);
		close(ms->mypipe[1]);
		*in = ms->mypipe[0];
	}
	return ;
}

char				*replace_tabs(char *line)
{
	int i;

	i = 0;
	while (line && line[i])
	{
		if (ft_isspace(line[i]))
			line[i] = ' ';
		i++;
	}
	return (line);
}

int					check_line(char *line)
{
	int stat;

	stat = 0;
	if (line[0] == ';' && line[1] == ';')
	{
		stat++;
		syntax_error(";;");
		errno = 258;
	}
	else if (line[0] == ';')
	{
		stat++;
		syntax_error(";");
		errno = 258;
	}
	return (stat);
}
