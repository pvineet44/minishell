/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 12:50:11 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/22 18:17:33 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_home_not_set(void)
{
	errno = 1;
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd("HOME not set\n", STDERR_FILENO);
}

void	ms_cd(char *path, t_minishell_meta *ms)
{
	int		ret;
	char	**tmp;

	ret = 0;
	errno = 0;
	tmp = ft_split(path, ' ');
	if (ft_strcmp(path, "") == 0)
	{
		substitute_value("$HOME", 0, ms);
		if ((ret = chdir(ms->arg)) == -1)
			print_home_not_set();
		ft_free(&ms->arg);
		free_tab(tmp);
		return ;
	}
	ret = chdir(tmp[0]);
	if (ret < 0)
	{
		errno = 1;
		no_file_or_directory("cd", tmp[0]);
		free_tab(tmp);
		// ft_putstr_fd(SHELL_NAME, STDOUT_FILENO);
		// ft_putstr_fd(": cd: ", STDOUT_FILENO);
		// ft_putstr_fd(tmp[0], STDOUT_FILENO);
		// ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
		return ;
	}
	free_tab(tmp);
}
