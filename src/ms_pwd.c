/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:17:59 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/15 16:35:51 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					ms_pwd(void)
{
	char *buff;

	errno = 0;
	buff = NULL;
	buff = getcwd(buff, sizeof(buff));
	ft_putendl_fd(buff, STDOUT_FILENO);
	ft_free(&buff);
	return ;
}
