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

int				check_var(char *var)
{
	int		i;

	i = 0;
	while ((var[i] != '=' && var[i] != '\0') ||\
	(!ft_isalpha(var[0]) && var[0] != '_'))
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
			ft_putstr_fd(var, STDOUT_FILENO);
			ft_putstr_fd("\': not a valid identifier\n", STDOUT_FILENO);
			return (0);
		}
		i++;
	}
	if (var[i] == '\0')
		return (0);
	return (1);
}

void			ms_export(char **env, char *arg)
{
	int		i;

	i = 0;
	if (check_var(arg))
	{
		while (env[i] != 0)
			i++;
		env[i] = ft_strdup(arg);
		env[++i] = 0;
	}
}
