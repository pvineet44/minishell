/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 12:47:40 by mashar            #+#    #+#             */
/*   Updated: 2020/04/11 08:48:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			previous_is_eof(int *ret, int *eof, char **line,\
t_minishell_meta *ms)
{
	char		*bef_line;
	char		*new_line;

	bef_line = *line;
	new_line = 0;
	*ret = get_next_line(0, &new_line);
	check_ret_lt_zero(ret, new_line, line, ms);
	check_ret_eq_zero(ret, new_line, bef_line, ms);
	if (errno != 1)
		errno_ne_one(line, bef_line, new_line);
	else
		errno_eq_one(line, new_line);
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

static int			current_line_handle(int *ret, int *eof, char **line,\
t_minishell_meta *ms)
{
	*ret = get_next_line(0, &(*line));
	if (*ret == -1)
	{
		ft_free(line);
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
	check_ret_and_line(ret, line, ms);
	return (1);
}

int					reset_errno_and_return(int tmp_errno)
{
	if (errno != 1)
		errno = tmp_errno;
	return (1);
}

int					get_line(char **line, t_minishell_meta *ms)
{
	static int	ret;
	static int	eof;
	int			tmp_errno;

	tmp_errno = errno;
	if (eof)
	{
		if (!previous_is_eof(&ret, &eof, line, ms))
			return (reset_errno_and_return(tmp_errno));
	}
	else
	{
		if (!current_line_handle(&ret, &eof, line, ms))
			return (reset_errno_and_return(tmp_errno));
	}
	if (errno != 1)
		errno = tmp_errno;
	return (0);
}
