/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:18:55 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/26 17:18:56 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					spawn_proc(t_minishell_meta *ms, char *line, int in, int i)
{
	pid_t pid;
	int out;

	out = ms->mypipe[1];
	if ((pid = fork ()) == 0)
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
		if (process_builtin(ms, i, line) == 0)
			search_and_execute_path(ms, i);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}
