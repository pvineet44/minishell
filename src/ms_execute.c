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
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
}

static void		write_permission_denied(char *path)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("Permission denied\n", STDERR_FILENO);
	errno = 126;
}

int				check_file_permission(char *path)
{
	struct stat file_stat;

	if (stat(path, &file_stat) >= 0 && ((file_stat.st_mode & S_IXUSR) == 0))
	{
		write_permission_denied(path);
		return (0);
	}
	return (1);
}

void			free_used_values(char *args1, char *args2, char **av)
{
	free_tab(av);
	ft_free(&args1);
	ft_free(&args2);
}

void			ms_execute(char *path, char **args, char **env, int len)
{
	pid_t	pid;
	int		i;
	int		x;

	i = 0;
	x = 1;
	errno = 0;
	char **av = (char**)malloc(sizeof(char*) * (len + 2));
	if (av == NULL)
		ms_exit(NULL, NULL, 0);
	av[0] = ft_strdup(path);
	while (args[i] != 0 && len != 0)
	{
		av[i + 1] = ft_strdup(args[i]);
		i++;
	}
	av[i + 1] = 0;
	pid = fork();
	signal(SIGINT, proc_signal_handler);
	signal(SIGQUIT, proc_sigquit_handler);
	if (pid == 0)
	{
	 	x = execve(path, av, env);
	}
	if (x == -1)
	{
		write_error(path);
		exit(127);
		return ;
	}
	wait(&errno);
	errno = errno / 255;
	free_tab(av);
}
