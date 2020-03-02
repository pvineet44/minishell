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
		ret = chdir(ms->arg);
		ft_free(&ms->arg);
		return ;
	}
	ret = chdir(tmp[0]);
	if (ret < 0)
	{
		errno = 1;
		ft_putstr_fd(SHELL_NAME, STDOUT_FILENO);
		ft_putstr_fd(": cd: ", STDOUT_FILENO);
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
		return ;
	}
	free_tab(tmp);
}
