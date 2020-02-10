/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:17:59 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/05 15:42:22 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					ms_pwd()
{
	char *buff;

	buff = NULL;
	buff = getcwd(buff, sizeof(buff));
	ft_putendl_fd(buff, 0);
	free(buff);
}
