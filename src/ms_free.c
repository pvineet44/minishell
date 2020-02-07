/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:27:26 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 11:22:22 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					free_all(t_minishell_meta *ms, char *line)
{
	int i;

	i = 0;
	free(line);
	line = 0;
	while (ms->args[i])
	{
		free(ms->args[i]);
		i++;
	}
	free(ms->args);
	ms->args = 0;
}
