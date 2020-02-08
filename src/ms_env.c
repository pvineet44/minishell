/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:44:57 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/08 15:02:39 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void						ms_env(t_minishell_meta *ms)
{
	char	nl;
	int		i;

	i = 0;
	nl = 10;
	(void)ms;
	while (ms->env[i])
	{
		write(1, ms->env[i], ft_strlen(ms->env[i]));
		write(1, &nl, 1);
		i++;
	}
}
