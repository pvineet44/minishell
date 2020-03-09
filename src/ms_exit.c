/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:06:45 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 11:21:25 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	int					check_numeric_arg(char *line)
{
	int i;

	i = 0;
	if (line == NULL)
		return (0);
	if (line[i] == '-')
	{
		if (ft_isdigit(line[i + 1]) == 0)
			return (0);
		i++;
	}
	while(line && line[i])
	{
		if (ft_isdigit(line[i]) == 0)
			return(0);
		i++;
	}
	return (1);
}

static	void				numeric_arg_required(char *line)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd(NUMERIC_ARGUMENT_REQUIRED, STDERR_FILENO);
}

void						ms_exit(t_minishell_meta *ms, char *line, int i)
{
	int stat;
	int len_args;

	len_args = ft_tablen(ms->piped_cmds->args1[i]);
	if (len_args == 0)
		stat = 0;
	else if (len_args > 1)
	{
		errno = 1;
		too_many_args("exit");
		return;
	}
	else if (check_numeric_arg(ms->piped_cmds->args1[i][0]))
		stat = ft_atoi(ms->piped_cmds->args1[i][0]);
	else
	{
		numeric_arg_required(ms->piped_cmds->args1[i][0]);
		stat = 255;
	}
	write(STDOUT_FILENO, EXIT_MSG, 5);
	free_all(ms, line);
	free_tab(ms->path);
	if (ms)
		free(ms);
	exit(stat);
}
