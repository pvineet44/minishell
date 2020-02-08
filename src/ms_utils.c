/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:10:08 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/08 13:07:19 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_quotes(char *line, int i, t_minishell_meta *ms)
{
	int		quote_bit;
	char	quote;

	quote = line[i];
	quote_bit = line[i] == '\'' ? 1 : 0;
	i++;
	while ((line[i] != '\0') && (line[i] != quote))
	{
		ms->arg = ft_stradd(ms->arg, line[i]);
		i++;
	}
	if (line[i] != quote)
		return (0);
	return (i);
}

int		substitute_value(char *line, int i, t_minishell_meta *ms)
{
	(void)ms;
	(void)line;
	return (i);
}

void	command_not_found(char *command)
{
	write(1, "minishell: ", 11);
	write(1, command, ft_strlen(command));
	write(1, COMMAND_NOT_FOUND, 20);
}
