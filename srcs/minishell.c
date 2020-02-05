/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:20:14 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/05 12:40:50 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, const char *argv[])
{
	char *line;
	int fd;
	t_minishell_meta ms;

	fd = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'x')
			break;
	}
	return 0;
}
