/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:10:08 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/09 18:03:08 by mashar           ###   ########.fr       */
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
		if (line[i] == '\\' && line[i + 1] == '\"' && !quote_bit)
		{
			ms->arg = ft_stradd(ms->arg, line[i + 1]);
			i = i + 2;
			continue;
		}
		if (line[i] == '$' && !quote_bit)
		{
			i = substitute_value(line, i, ms);
			i++;
			continue;
		}
		ms->arg = ft_stradd(ms->arg, line[i]);
		i++;
	}
	if (line[i] != quote)
		return (0);
	return (i);
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
	int		j;
	char	*var;

	var = NULL;
	j = i;
	i++;
	if (line[i] == '?')
		return (i + get_exit_status(ms));
	if (ft_isdigit(line[i]))
		return (i);
	if (!ft_isalpha(line[i]) && line[i] != '_')
	{
		if (line[i] != '\'' && line[i] != '\"')
			write(STDOUT_FILENO, "$", 1);
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
	if (ms->piped_cmds->files[i][0] != '\0')
		unset_fd(ms);
	write(STDOUT_FILENO, "minishell: ", 11);
	write(STDOUT_FILENO, ms->piped_cmds->cmds[i],
	ft_strlen(ms->piped_cmds->cmds[i]));
	write(STDOUT_FILENO, COMMAND_NOT_FOUND, 20);
	errno = 127;
}

int		ft_isredir(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
