/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:08:26 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 12:08:43 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_meta					*init_minishell_meta(t_minishell_meta *ms)
{
	ms->cmd = 0;
	ms->arg_start = 0;
	ms->arg_bit = 0;
	ms->opt_bit = 0;
	return (ms);
}
