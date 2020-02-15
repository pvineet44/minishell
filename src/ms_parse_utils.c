/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:52:37 by mashar            #+#    #+#             */
/*   Updated: 2020/02/13 15:52:40 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char       *get_redir(char *redir, char *line, t_minishell_meta *ms)
{
    int     i;

    i = 0;
    redir = NULL;
    if (line[i] == '\0')
        return (ft_strdup(""));
    while (ft_isredir(line[i]) && line[i] != '\0')
    {
        redir = ft_stradd(redir, line[i]);
        i++;
    }
    ms->arg_start += i;
    return (redir);
}

char    *get_file(char *file, char *line, t_minishell_meta *ms)
{
    int     i;

    i = 0;
    (void)ms;
    file = NULL;
    while (ft_isspace(line[i]))
        i++;
    if (line[i] == '\0')
        return (ft_strdup(""));
    while (line[i] != '\0')
    {
        file = ft_stradd(file, line[i]);
        i++;
    }
    return (file);
}