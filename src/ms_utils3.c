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