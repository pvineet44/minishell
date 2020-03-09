/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:47:40 by mashar            #+#    #+#             */
/*   Updated: 2020/03/09 12:47:42 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char        *get_line(char *line, char *tmp_line)
// {
//     int     i;

//     ft_putstr_fd("  \b\b", STDOUT_FILENO);
//     if (tmp_line != NULL)
//         return (tmp_line);
//     i = 0;
//     while (line[i] != '\0')
//     {
//         tmp_line = ft_stradd(tmp_line, line[i]);
//         i++;
//     }
//     return (tmp_line);
// }

// char        *join_tmp_line(char **tmp_line, char *line)
// {
//     char *ret_line;

//     ret_line = 0;
//     ft_putendl_fd(*tmp_line, 2);
//     if (*tmp_line == 0)
//         return (line);
//     ret_line = ft_strjoin(*tmp_line, line);
//     *tmp_line = 0;
//     line = 0;
//     return (ret_line);
// }


static int
	previous_is_eof(int *ret, int *eof, char **line,\
    t_minishell_meta *ms)
{
	char		*bef_line;
	char		*new_line;

	bef_line = *line;
	new_line = 0;
	if ((*ret = get_next_line(0, &new_line)) < 0)
	{
        ft_free(line);
		free_tab(ms->path);
		free(ms);
        exit(0);
    }
	*line = ft_strjoin(bef_line, new_line);
	free(bef_line);
	free(new_line);
	if (*ret > 0)
		*eof = 0;
	if (*ret == 0)
	{
		ft_putstr("  \b\b");
		return (0);
	}
	return (1);
}

static int
	current_line_handle(int *ret, int *eof, char **line,\
    t_minishell_meta *ms)
{
	*ret = get_next_line(0, &(*line));
	if (*ret == -1)
	{
        ft_free(line);
		free_tab(ms->path);
		free(ms);
        exit(0);
    }
	if ((*ret == 0 && ft_strlen(*line)))
	{
		*eof = 1;
		ft_putstr("  \b\b");
		return (0);
	}
	if (*ret == 0 && !ft_strlen(*line))
	{
        ft_free(line);
		free_tab(ms->path);
		free(ms);
		write(1, " exit\n", 6);
		exit(0);
	}
	return (1);
}


int    get_line(char **line, t_minishell_meta *ms)
{
    static int	ret;
	static int	eof;

    if (eof)
	{
		if (!previous_is_eof(&ret, &eof, line, ms))
			return (1);
	}
    else
	{
		if (!current_line_handle(&ret, &eof, line, ms))
			return (1);
	}
   	return (0);
}