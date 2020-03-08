/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:20:21 by vparekh           #+#    #+#             */
/*   Updated: 2020/03/03 13:20:22 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void            no_file_or_directory(char *cmd, char *name)
{
    ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    if (cmd)
    {
        ft_putstr_fd(cmd, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    if (name)
    {
        ft_putstr_fd(name, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
}

void            too_many_args(char *cmd)
{
    ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
}

void            syntax_error(char *token)
{
    ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
    ft_putstr_fd(SYNTAX_ERROR, STDERR_FILENO);
    ft_putstr_fd(token, STDERR_FILENO);
    ft_putstr_fd("'\n", STDERR_FILENO);
}

int             check_line(char *line)
{
    int stat;
    stat = 0;
    if (line[0] == ';' && line[1] == ';')
    {
        stat++;
        syntax_error(";;");
    }
    else if (line[0] == ';')
    {
        stat++;
        syntax_error(";");
    }
    errno = 258;
    return (stat);
}