/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:20:21 by vparekh           #+#    #+#             */
/*   Updated: 2020/03/03 13:20:22 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			no_file_or_directory(char *cmd, char *name)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (name)
	{
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
}

void			too_many_args(char *cmd)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
}

void			syntax_error(char *token)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(SYNTAX_ERROR, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	errno = 258;
}

void			print_invalid(char *var, char *cmd)
{
	errno = 1;
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(cmd, STDOUT_FILENO);
	ft_putstr_fd(": `", STDOUT_FILENO);
	ft_putstr_fd(var, STDOUT_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDOUT_FILENO);
}

int				get_frequency(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
