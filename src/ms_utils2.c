/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:28:53 by vparekh           #+#    #+#             */
/*   Updated: 2020/03/02 11:51:31 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				terminate_tabs(t_minishell_meta *ms, int j)
{
	ms->piped_cmds->cmds[j] = 0;
	ms->piped_cmds->args[j] = 0;
	ms->piped_cmds->files[j] = 0;
	ft_free(&ms->arg);
}
