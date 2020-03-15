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
	if (*ret == 0 && errno == 1 && !ft_strlen(new_line))
	{
		ft_free(&bef_line);
		ft_free(&new_line);
		free_tab(ms->path);
		write(1, " exit\n", 6);
		free_tab(ms->export);
		free(ms);
		exit(0);
	}
	if (errno != 1)
	{
		*line = ft_strjoin(bef_line, new_line);
		free(bef_line);
		free(new_line);
	}
	else
	{
		ft_free(line);
		*line = ft_strdup(new_line);
		ft_free(&new_line);
	}
	if (*ret == 1 && errno == 2)
	{
		ft_putstr("  \b\b");
		return (0);
	}
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
		free_tab(ms->env);
		free(ms);
        exit(0);
    }
	if (*ret == 1 && errno == 2)
	{
		*eof = 1;
		ft_putstr("  \b\b");
		return (0);
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
		write(1, " exit\n", 6);
		free_tab(ms->export);
		free_tab(ms->env);
		free(ms);
		exit(0);
	}
	return (1);
}


int    get_line(char **line, t_minishell_meta *ms)
{
    static int	ret;
	static int	eof;
	int			tmp_errno;

	tmp_errno = errno;
    if (eof)
	{
		if (!previous_is_eof(&ret, &eof, line, ms))
		{
			if (errno != 1)
				errno = tmp_errno;
			return (1);
		}
	}
    else
	{
		if (!current_line_handle(&ret, &eof, line, ms))
		{
			if (errno != 1)
				errno = tmp_errno;
			return (1);
		}
	}
	if (errno != 1)
		errno = tmp_errno;
   	return (0);
}