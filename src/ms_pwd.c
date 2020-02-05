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

void					ms_pwd(t_minishell_meta *ms)
{
	char nl;
	char *buff;

	(void)ms;
	buff = NULL;
	nl = '\n';
	buff = getcwd(buff, sizeof(buff));
	write(1, buff, ft_strlen(buff));
	write(1, &nl, 1);
	free(buff);
}
