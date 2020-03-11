/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:12:04 by mashar            #+#    #+#             */
/*   Updated: 2020/02/09 18:01:36 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_invalid(char *var, char *cmd)
{
	errno = 1;
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(cmd, STDOUT_FILENO);
	ft_putstr_fd(": `", STDOUT_FILENO);
	ft_putstr_fd(var, STDOUT_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDOUT_FILENO);
}

int				check_var(char *var, char *cmd)
{
	int		i;

	i = 0;
	while ((var[i] != '=' && var[i] != '\0') ||\
	(!ft_isalpha(var[0]) && var[0] != '_'))
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			print_invalid(var, cmd);
			return (0);
		}
		i++;
	}
	if (var[i] != '\0' && (ft_strcmp(cmd, "unset") == 0))
	{
		print_invalid(var, cmd);
		return (0);
	}
	return (1);
}

static void 	print_export_env(char **env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i] != 0)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = 0;
		while (env[i][j] != '\0')
		{
			ft_putchar_fd(env[i][j], STDOUT_FILENO);
			if (env[i][j] == '=')
				ft_putchar_fd('\"', STDOUT_FILENO);
			j++;
		}
        if (ft_strchr(env[i], '=') != NULL)
			ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}

void			unset_var(char *var, t_minishell_meta *ms)
{
	int i;
	char *tmp_var;

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

int				not_in_env(char **env, char *var)
{
	int		env_len;
	int		var_len;
	int		i;

	i = -1;
	var_len = ft_strlen(var);
	while (env[++i] != '\0')
	{
		env_len = 0;
		while (env[i][env_len] != '=' && env[i][env_len] != '\0')
			env_len++;
		if (var_len != env_len)
			continue;
		if (ft_strncmp(var, env[i], var_len) != 0)
			continue;
		return (0);
	}
	return (1);
}

void			ms_export(t_minishell_meta *ms, int i)
{
	int		j;
	int		k;
    
	k = 0;
	j =0;
	errno = 0;
	if (ms->piped_cmds->args1[i][0] == NULL && ms->no_args)
	{
		print_export_env(ms->env);
		print_export_env(ms->export);
		return ;
	}
	while (ms->piped_cmds->args1[i][k] != 0)
	{
		j = 0;
		if (check_var(ms->piped_cmds->args1[i][k], "export"))
		{
			if (ft_strchr(ms->piped_cmds->args1[i][k], '=') != NULL)
            {
                unset_var(ms->piped_cmds->args1[i][k], ms);
			    while (ms->env[j] != 0)
				    j++;
			    ms->env[j] = ft_strdup(ms->piped_cmds->args1[i][k]);
			    ms->env[++j] = 0;
                j = 0;
            }
            else if (not_in_env(ms->env, ms->piped_cmds->args1[i][k]))
            {
				ms_unset_single(ms->export, ms->piped_cmds->args1[i][k], ms->path);
                while (ms->export[j] != 0)
				    j++;
			    ms->export[j] = ft_strdup(ms->piped_cmds->args1[i][k]);
			    ms->export[++j] = 0;
            }
		}
		if (ft_strncmp(ms->piped_cmds->args1[i][k], "PATH=",5) == 0)
			set_path(ms);
		k++;
	}
}
