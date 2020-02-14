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

void			reset_bits(t_minishell_meta *ms)
{
	ms->arg_bit = 0;
	ms->opt_bit = 0;
	ms->arg_start = 0;
	ms->process_bit = 0;
	ms->arg = 0;
	ms->file_fd = -1;
	ms->out_fd = -1;
	ms->in_fd = -1;
}
