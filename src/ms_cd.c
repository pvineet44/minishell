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

void	ms_cd(char *path)
{
	int ret;

	ret = 0;
	ret = chdir(path);
	errno = 0;
	ft_putnbr_fd(errno, STDOUT_FILENO);
	if (ret < 0)
	{
		errno = 1;
		ft_putnbr_fd(errno, STDOUT_FILENO);
		ft_putstr_fd(SHELL_NAME, STDOUT_FILENO);
		ft_putstr_fd(": cd: ", STDOUT_FILENO);
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
		return ;
	}
}
