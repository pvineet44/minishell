/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:17:59 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/05 15:34:36 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					ms_pwd(t_minishell_meta *ms)
{
	char nl;

	nl = '\n';
	ms->output = getcwd(ms->output, sizeof(ms->output));
	write(1, ms->output, ft_strlen(ms->output));
	write(1, &nl, 1);
}
