/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:35:06 by mashar            #+#    #+#             */
/*   Updated: 2020/04/10 19:25:54 by user42           ###   ########.fr       */
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

void			write_permission_denied(char *path)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("Permission denied\n", STDERR_FILENO);
	errno = 126;
}

void			free_used_values(char *args1, char *args2, char **av)
{
	free_tab(av);
	ft_free(&args1);
	ft_free(&args2);
}

void			fork_process(char *path, char **av, char **env)
{
	pid_t	pid;
	int		x;

	x = 1;
	pid = fork();
	if (1)
	{
		signal(SIGINT, proc_signal_handler);
		signal(SIGQUIT, proc_sigquit_handler);
	}
	if (pid == 0)
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
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
}

void			ms_execute(char *path, char **args, char **env)
{
	int		i;
	int		len;
	char	**av;

	i = 0;
	errno = 0;
	len = ft_tablen(args);
	if (check_file_permission(path) == 0)
		return ;
	av = (char**)malloc(sizeof(char*) * (len + 2));
	if (av == NULL)
		ms_exit(NULL, NULL, 0);
	av[0] = ft_strdup(path);
	while (args[i] != 0 && len != 0)
	{
		av[i + 1] = ft_strdup(args[i]);
		i++;
	}
	av[i + 1] = 0;
	fork_process(path, av, env);
}
