/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:58:42 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/05 16:43:33 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					parse(t_minishell_meta *ms, char *line)
{
	if (ft_strcmp(line, CMD_EXIT) == 0)
		ms->cmd = 'x';
	if (ft_strcmp(line, CMD_PWD) == 0)
		ms->cmd = 'p';
	if (ft_strcmp(line, CMD_ENV) == 0i)
		ms->cmd = 'n';
	return ;
}
