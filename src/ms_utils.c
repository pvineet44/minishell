/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:10:08 by vparekh           #+#    #+#             */
/*   Updated: 2020/04/11 22:42:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_quotes(char *line, int i, t_minishell_meta *ms)
{
	int		quote_bit;
	char	quote;

	quote = line[i];
	quote_bit = line[i++] == '\'' ? 1 : 0;
	while ((line[i] != '\0') && (line[i] != quote))
	{
		if (line[i] == '\\' && ((line[i + 1] == '\"' && !quote_bit)\
		|| (line[i + 1] == '\\' && !quote_bit) || line[i + 1] == '$'))
		{
			ms->arg = ft_stradd(ms->arg, line[i + 1]);
			i = i + 2;
			continue;
		}
		if (line[i] == '$' && !quote_bit && ft_isalpha(line[i + 1]))
		{
			i = substitute_value(line, i, ms);
			i++;
			continue;
		}
		ms->arg = ft_stradd(ms->arg, line[i]);
		i++;
	}
	return (line[i] != quote ? 0 : i);
}

void	add_env(t_minishell_meta *ms, char *var)
{
	int		env_len;
	int		var_len;
	int		i;

	i = -1;
	var_len = ft_strlen(var);
	while (ms->env[++i] != 0)
	{
		env_len = 0;
		while (ms->env[i][env_len] != '=')
			env_len++;
		if (var_len != env_len)
			continue;
		if (ft_strncmp(var, ms->env[i], var_len) != 0)
			continue;
		env_len++;
		while (ms->env[i][env_len] != '\0')
		{
			ms->arg = ft_stradd(ms->arg, ms->env[i][env_len]);
			env_len++;
		}
		break ;
	}
}

int		substitute_value(char *line, int i, t_minishell_meta *ms)
{
	char	*var;

	var = NULL;
	i++;
	if (line[i] == '?')
		return (i + get_exit_status(ms));
	if (ft_isdigit(line[i]))
		return (i);
	if (!ft_isalpha(line[i]) && line[i] != '_')
	{
		if (line[i] != '\'' && line[i] != '\"')
			ms->arg = ft_stradd(ms->arg, '$');
		return (i - 1);
	}
	while (line[i] && \
	(ft_isalpha(line[i]) || ft_isdigit(line[i]) || line[i] == '_'))
	{
		var = ft_stradd(var, line[i]);
		i++;
	}
	add_env(ms, var);
	free(var);
	return ((i - 1));
}

void	command_not_found(t_minishell_meta *ms, int i)
{
	if (ms->piped_cmds->files1[i][0] != 0)
		unset_fd(ms);
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, ms->piped_cmds->cmds[i],
	ft_strlen(ms->piped_cmds->cmds[i]));
	write(STDERR_FILENO, COMMAND_NOT_FOUND, 20);
	errno = 127;
}

int		ft_isredir(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
