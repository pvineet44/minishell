/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:18:55 by vparekh           #+#    #+#             */
/*   Updated: 2020/03/02 11:46:41 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
