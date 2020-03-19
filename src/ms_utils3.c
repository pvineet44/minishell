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

void			no_file_or_directory(char *cmd, char *name)
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

void			too_many_args(char *cmd)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
}

void			syntax_error(char *token)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(SYNTAX_ERROR, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	errno = 258;
}

void			print_invalid(char *var, char *cmd)
{
	errno = 1;
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(cmd, STDOUT_FILENO);
	ft_putstr_fd(": `", STDOUT_FILENO);
	ft_putstr_fd(var, STDOUT_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDOUT_FILENO);
}

int				check_line(char *line)
{
	int stat;

	stat = 0;
	if (line[0] == ';' && line[1] == ';')
	{
		stat++;
		syntax_error(";;");
		errno = 258;
	}
	else if (line[0] == ';')
	{
		stat++;
		syntax_error(";");
		errno = 258;
	}
	return (stat);
}

char			*fetch_redir(char *line, int *i)
{
	char	*redir_seq;
	int		j;

	j = *i;
	redir_seq = NULL;
	redir_seq = ft_stradd(redir_seq, line[*i]);
	j++;
	if (line[j] == '>')
	{
		redir_seq = ft_stradd(redir_seq, line[j]);
		j++;
	}
	*i = j;
	return (redir_seq);
}

int				check_invalid_redir(char *line, int i,\
t_minishell_meta *ms)
{
	char *redir_seq;
	char *tmp;

	redir_seq = fetch_redir(line, &i);
	if (ms->arg == NULL)
		tmp = ft_strdup(redir_seq);
	else
		tmp = ft_strjoin(ms->arg, redir_seq);
	ft_free(&ms->arg);
	ms->arg = ft_strdup(tmp);
	ft_free(&tmp);
	ft_free(&redir_seq);
	if (line[i] == 0)
	{
		syntax_error("newline");
		ft_free(&ms->arg);
		return (0);
	}
	else if (ft_isredir(line[i]))
	{
		redir_seq = fetch_redir(line, &i);
		syntax_error(redir_seq);
		ft_free(&redir_seq);
		ft_free(&ms->arg);
		return (0);
	}
	ft_free(&redir_seq);
	return (i);
}
