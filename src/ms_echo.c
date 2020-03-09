/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:33:37 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 17:12:55 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				ms_echo(char **args)
{
	int i;
	int c;

	i = 0;
	c = 0;
	if (args[0] == NULL)
		c = 0;
	else if (ft_strcmp(args[i], "-n") == 0)
	{
		c = 1;
		i++;
	}
	while(args[i])
	{
	
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (c != 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
