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
	if (var[i] == '\0' && (ft_strcmp(cmd, "export") == 0))
		return (0);
	if (var[i] != '\0' && (ft_strcmp(cmd, "unset") == 0))
	{
		print_invalid(var, cmd);
		return (0);
	}
	return (1);
}

static void		print_export_env(char **env)
{
	int		i;
	int		j;

	i = 0;
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
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		i++;
	}
}

void			ms_export(t_minishell_meta *ms, int i)
{
	int		j;

	j = 0;
	if (ft_strcmp(ms->piped_cmds->args[i], "") == 0)
	{
		print_export_env(ms->env);
		return ;
	}
	if (check_var(ms->piped_cmds->args[i], "export"))
	{
		while (ms->env[j] != 0)
			j++;
		ms->env[j] = ft_strdup(ms->piped_cmds->args[i]);
		ms->env[++j] = 0;
		errno = 0;
	}
	if (ft_strncmp(ms->piped_cmds->args[i], "PATH=",5) == 0)
		set_path(ms);
}
