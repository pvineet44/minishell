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

void                            handle_pipe(t_minishell_meta *ms, int i)
{
    (void)i;
    ms->in_fd = dup(STDIN_FILENO);
    ms->out_fd = dup(STDOUT_FILENO);
    if (pipe(ms->mypipe))
    {
        write(1,"Failed\n", 7);
        exit(EXIT_FAILURE);
    }
}

void                            process_pipe(t_minishell_meta *ms, int i, char *line)
{
    int stat;
    pid_t pid;
    pid = fork();
    if (pid == (pid_t) 0)
    {
        close(ms->mypipe[0]);
        dup2(ms->mypipe[1], STDOUT_FILENO);
        if (process_builtin(ms, i, line) == 0)
			search_and_execute_path(ms, i);
        exit(EXIT_SUCCESS);
    }
    wait(&stat);
    close(ms->mypipe[1]);
    dup2(ms->mypipe[0], STDIN_FILENO);
    close(ms->mypipe[0]);
    // unset_fd(ms);
    return ;
}
