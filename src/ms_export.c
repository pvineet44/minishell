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
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i] != '=' && var[i] != '\0')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			ft_putstr("minishell: export: `");
			ft_putstr(var);
			ft_putstr("\': not a valid identifier\n");
			return (0);
		}
		i++;
	}
	if (var[i] == '\0')
		return (0);
	return (1);
}

void			ms_export(t_minishell_meta *ms)
{
	int		i;

	i = 0;
	if (check_var(ms->arg))
	{
		while (ms->env[i] != 0)
			i++;
		ms->env[i] = ft_strdup(ms->arg);
		ms->env[++i] = 0;
	}
}
