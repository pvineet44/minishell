/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_file_descriptor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 13:23:50 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/15 16:46:00 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					unset_fd(t_minishell_meta *ms)
{
	if (ms->file_fd == 1)
		close(ms->file_fd);
	if (ms->out_fd != -1)
		dup2(ms->out_fd, 1);
	if (ms->in_fd != -1)
		dup2(ms->in_fd, 0);
	close(ms->in_fd);
}

void					set_in_fd(t_minishell_meta *ms, char *filename)
{
	if (ms->file_fd != -1)
	{
		ms->in_fd = dup(STDIN_FILENO);
		close(STDIN_FILENO);
	}
	else
		close(ms->file_fd);
	ms->file_fd = open(filename, O_RDONLY);
	if (ms->file_fd < 0 && (ms->process_bit = -1))
	{
		close(ms->file_fd);
		ms->file_fd = -1;
		dup2(ms->in_fd, 0);
		no_file_or_directory(NULL, filename);
	}
}

void					set_out_fd(t_minishell_meta *ms, char *filename,
int is_append)
{
	if (ms->file_fd != 1)
	{
		ms->out_fd = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
	}
	else
		close(ms->file_fd);
	if (is_append)
		ms->file_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		ms->file_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

void					call_actual_handle(char *filename, char *redir,
t_minishell_meta *ms, int i)
{
	int j;

	j = 0;
	if (filename == NULL && redir == NULL)
		return ;
	if (redir == NULL)
	{
		while (filename[j] != '\0')
			ms->piped_cmds->args[i] = ft_stradd(ms->piped_cmds->args[i],
			filename[j++]);
		ms->piped_cmds->args[i] = ft_stradd(ms->piped_cmds->args[i], 32);
		return ;
	}
	if (ft_strcmp(redir, ">>") == 0)
		set_out_fd(ms, filename, 1);
	else if ((ft_strcmp(redir, "><") == 0) && (ms->process_bit = -1))
		return syntax_error("<");
	else if ((ft_strcmp(redir, "<>") == 0) &&(ms->multiline = -99))
		set_in_fd(ms, filename);
	else if (redir[0] == '>')
		set_out_fd(ms, filename, 0);
	else if (redir[0] == '<')
		set_in_fd(ms, filename);
}

void					handle_fd(char *line, t_minishell_meta *ms, int index)
{
	char			*filename;
	char			*redir;
	int				i;

	i = 0;
	if (line == NULL)
		return ;
	filename = NULL;
	redir = NULL;
	while (line[i] != '\0')
	{
		while ((line[i] != '\0' && ft_isspace(line[i])))
			i++;
		while (line[i] != '\0' && ft_isredir(line[i]))
			redir = ft_stradd(redir, line[i++]);
		while ((line[i] != '\0' && ft_isspace(line[i])))
			i++;
		while (line[i] != '\0' && !ft_isspace(line[i]) && !ft_isredir(line[i]))
			filename = ft_stradd(filename, line[i++]);
		call_actual_handle(filename, redir, ms, index);
		ft_free(&redir);
		ft_free(&filename);
	}
}
