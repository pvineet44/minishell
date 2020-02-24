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

static	int			check_opt_bit(char *arg)
{
	if (ft_strncmp("-n ", arg, 3) == 0)
		return (1);
	if (ft_strncmp("-n", arg, 2) == 0 && arg[3] == '\0')
		return (1);
	return (0);
}

void				ms_echo(char *arg)
{
	int		i;
	int		c;
	char	*buff;

	buff = NULL;
	errno = 0;
	if (arg[0] == '\0')
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	c = 0;
	i = 0;
	buff = arg;
	c = check_opt_bit(arg);
	if (c == 1)
		buff = &arg[3];
	i = ft_strlen(buff);
	while (buff && ft_isspace(buff[i - 1]))
		i--;
	write(STDOUT_FILENO, buff, i);
	if (c != 1)
		write(STDOUT_FILENO, "\n", 1);
}
