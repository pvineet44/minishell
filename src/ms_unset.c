/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 15:53:48 by mashar            #+#    #+#             */
/*   Updated: 2020/02/09 17:02:52 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_var(char *var, t_minishell_meta *ms)
{
	int		i;
	char	*tmp_var;

	i = 0;
	tmp_var = NULL;
	while (var[i] != '=')
	{
		tmp_var = ft_stradd(tmp_var, var[i]);
		i++;
	}
	ms_unset_single(ms->env, tmp_var, ms->path);
	ms_unset_single(ms->export, tmp_var, ms->path);
	ft_free(&tmp_var);
	return ;
}

void	free_path(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
	{
		ft_free(&args[i]);
		args[i] = 0;
		i++;
	}
	if (args)
		args = 0;
}

int		ms_unset_single(char **env, char *arg, char **path)
{
	int		env_len;
	int		i;

	i = -1;
	if (!check_var(arg, "unset"))
		return (0);
	while (env[++i] != 0)
	{
		env_len = (0);
		while (env[i][env_len] != '=' && env[i][env_len] != '\0')
			env_len++;
		if (ft_strlen(arg) != env_len)
			continue;
		if (ft_strncmp(arg, env[i], env_len) != 0)
			continue;
		ft_free(&env[i]);
		while (env[++i] != 0)
			env[i - 1] = env[i];
		env[--i] = 0;
		break ;
	}
	if (ft_strcmp(arg, "PATH") == 0)
		free_path(path);
	return (1);
}

void	ms_unset(t_minishell_meta *ms, int i)
{
	int	j;
	int valid_var;

	j = 0;
	errno = 0;
	if (ms->no_args)
		return ;
	while (ms->piped_cmds->args1[i][j] != 0)
	{
		valid_var = ms_unset_single(ms->env, ms->piped_cmds->args1[i][j],\
		ms->path);
		if (valid_var == 0)
		{
			j++;
			continue ;
		}
		ms_unset_single(ms->export, ms->piped_cmds->args1[i][j], ms->path);
		j++;
	}
}
