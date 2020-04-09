/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 19:46:19 by mashar            #+#    #+#             */
/*   Updated: 2020/04/09 22:22:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			set_export(t_minishell_meta *ms)
{
	int i;
	int env_len;

	i = 0;
	env_len = 0;
	while (ms->env[env_len] != 0)
		env_len++;
	ms->export = (char**)malloc(sizeof(char*) * (env_len + 1));
	if (ms->export == NULL)
		exit(1);
	ms->export[i] = 0;
	return ;
}

void			set_env(t_minishell_meta *ms, char **env)
{
	int i;
	int env_len;

	i = 0;
	env_len = 0;
	while (env[env_len] != 0)
		env_len++;
	ms->env = (char**)malloc(sizeof(char*) * (env_len + 100));
	if (ms->env == NULL)
		exit(0);
	while (i < env_len)
	{
		ms->env[i] = ft_strdup(env[i]);
		i++;
	}
	ms->env[i] = 0;
}

void			set_path(t_minishell_meta *ms)
{
	ms->arg = 0;
	substitute_value("$PATH", 0, ms);
	ms->path = ft_split(ms->arg, ':');
	ft_free(&ms->arg);
}

void			set_env_export(t_minishell_meta *ms, char **env)
{
	set_env(ms, env);
	set_export(ms);
	ms->path = 0;
	write(STDOUT_FILENO, SHELL_BANNER, 15);
}

int     add_ms_arg(t_minishell_meta *ms, int index, int j, int flag)
{
	if (flag == 0)
	{
		if (ms->arg)
		{
			ms->piped_cmds->redir[index][j] = ft_strdup(ms->arg);
			ft_free(&ms->arg);
		}
		else
			ft_free(&ms->arg);
		return (j);
	}
	else if (flag == 1)
	{
		if (ms->arg)
		{
			ms->piped_cmds->files1[index][j++] = ft_strdup(ms->arg);
			ft_free(&ms->arg);
		}
		return (j);
	}
	return (j);
}