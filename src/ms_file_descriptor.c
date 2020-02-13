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

void                    set_out_fd(char *arg, int *out)
{
    *out = open(arg, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    ft_putnbr_fd(*out, 0);
    dup2(*out, STDOUT_FILENO);
}

void                    set_in_fd(char *arg, int *in)
{
    *in = open(arg, O_RDONLY);
    dup2(*in, STDIN_FILENO);
}

void                    unset_fd(int *fd)
{
    close(*fd);
}