/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_descriptor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 13:23:50 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/11 13:23:56 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void                    set_out_fd(char *arg, t_minishell_meta *ms)
{
    ms->out_fd = dup(1);
    close(1);
    ms->file_fd = open(arg, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
}

void                    set_in_fd(char *arg, int *in)
{
    *in = open(arg, O_RDONLY);
    dup2(*in, STDIN_FILENO);
}

void                    unset_fd(t_minishell_meta *ms)
{
    if (ms->file_fd == 1)
        close(ms->file_fd);
    dup2(ms->out_fd, 1);
    close(ms->out_fd);
}

void                    call_actual_handle(char *filename, char *redir, t_minishell_meta *ms)
{
    if (ft_strcmp(redir, ">>"))
    {

    }
    // else if (ft_strcmp(redir, "<>"))
    // {

    // }
    // else 
    if (redir[0] == '>')
    {
        if (ms->file_fd != 1)
        {
            ms->out_fd = dup(STDOUT_FILENO);
            close(STDOUT_FILENO);
        }
        else
            close (ms->file_fd);
        ms->file_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    }
    // else if (redir[0] == '<')
    // {
    //     /* code */
    // }
    
}

void                    handle_fd(char *line, t_minishell_meta *ms)
{
    char *filename;
    char *redir;
    int i;

    i = 0;
    if (line == NULL)
        return ;
    filename = NULL;
    redir = NULL;
    while (line[i] != '\0')
    {
        while (line[i] != '\0' && ft_isredir(line[i]))
            redir = ft_stradd(redir, line[i++]);
        while (line[i] != '\0' && !ft_isspace(line[i]) && !ft_isredir(line[i]))
            filename = ft_stradd(filename, line[i++]);
        call_actual_handle(filename, redir, ms);
        ft_free(&redir);
        ft_free(&filename);
    }
}