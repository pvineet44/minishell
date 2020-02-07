/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:04:44 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 11:19:08 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					process(t_minishell_meta *ms, char *line)
{
	if (ms->cmd == 'x')
		ms_exit(ms, line);
	if (ms->cmd == 'p')
		ms_pwd(ms);
	if (ms->cmd == 'n')
		ms_env(ms);
}
