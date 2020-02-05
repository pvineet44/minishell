/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:44:57 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/05 17:48:14 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void						ms_env(t_minishell_meta *ms)
{
	(void)ms;
	char nl;
	nl = 10;
	while(*environ)
	{
		write(1, *environ, ft_strlen(*environ));
		write(1, &nl, 1);
		environ++;
	}
}
