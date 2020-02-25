/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:35:06 by mashar            #+#    #+#             */
/*   Updated: 2020/02/22 18:18:11 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		write_error(char *path)
{
	ft_putstr_fd(SHELL_NAME, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	ft_putstr_fd("No such file or directory", STDOUT_FILENO);
}

void			ms_execute(char *path, char *args, char **env)
{
	pid_t	pid;
	int		x;
	char	**av;
	char	*args1;
	char	*args2;

	errno = 0;
	args2 = ft_strjoin(path, " ");
	args1 = ft_strjoin(args2, args);
	av = ft_split(args1, ' ');
	x = 1;
	if ((pid = fork()) == 0)
		x = execve(path, av, env);
	if (x == -1)
	{
		write_error(path);
		exit(127);
		return ;
	}
	wait(&errno);
	errno = errno / 255;
	free_tab(av);
	ft_free(&args1);
	ft_free(&args2);
}
