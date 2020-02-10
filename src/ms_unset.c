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

void	ms_unset(t_minishell_meta *ms)
{
	int		env_len;
	int		var_len;
	int		i;

	i = -1;
	var_len = ft_strlen(ms->arg);
	while (ms->env[++i] != '\0')
	{
		env_len = 0;
		while (ms->env[i][env_len] != '=')
			env_len++;
		if (var_len != env_len)
			continue;
		if (ft_strncmp(ms->arg, ms->env[i], var_len) != 0)
			continue;
		i++;
		while (ms->env[i] != 0)
		{
			ms->env[i - 1] = ms->env[i];
			i++;
		}
		ms->env[--i] = 0;
		break ;
	}
}
