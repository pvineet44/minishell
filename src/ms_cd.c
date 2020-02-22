/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 12:50:11 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/22 12:50:12 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void                        ms_cd(char *path)
{
    int ret;

    ret = 0;
    ret = chdir(path);
    if (ret < 0)
    {
        ft_putstr_fd(SHELL_NAME, STDOUT_FILENO);
        ft_putstr_fd(": cd: ", STDOUT_FILENO);
        ft_putstr_fd(path, STDOUT_FILENO);
        ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
        return ;
    }
}