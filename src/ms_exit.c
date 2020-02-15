/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:06:45 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 11:21:25 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void						ms_exit(t_minishell_meta *ms, char *line)
{
	write(STDOUT_FILENO, EXIT_MSG, 5);
	free_all(ms, line);
	free(ms);
	exit(EXIT_SUCCESS);
}
