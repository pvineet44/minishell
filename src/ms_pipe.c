/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:18:55 by vparekh           #+#    #+#             */
/*   Updated: 2020/04/10 19:25:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			unset_fd(t_minishell_meta *ms)
{
	if (ms->file_fd == 1)
		close(ms->file_fd);
	if (ms->out_fd != -1)
		dup2(ms->out_fd, 1);
	if (ms->in_fd != -1)
	{
		dup2(ms->in_fd, 0);
		close(ms->in_fd);
	}
}

void			spawn_proc(t_minishell_meta *ms, char *line, int in, int i)
{
	pid_t	pid;
	int		out;
	int		stat;

	out = ms->mypipe[1];
	if ((pid = fork()) == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		process_cmd(ms, line, i);
		exit(errno);
	}
	waitpid(pid, &stat, 0);
	errno = stat / 255;
}
