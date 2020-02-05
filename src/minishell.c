/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:20:14 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/05 15:43:58 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, const char *argv[])
{
	char *line;
	int fd;

	(void)argc;
	(void)argv;
	t_minishell_meta *ms;
	signal (SIGINT, sig_int_handler);
	ms = malloc(sizeof(t_minishell_meta));
	if (ms == NULL)
		return (0);
	fd = 0;
	line = NULL;
	write(1, SHELL_BANNER, 14);
	while (get_next_line(fd, &line) > 0)
	{
		ms = init_minishell_meta(ms);
		parse(ms, line);
		process(ms);
		write(1, SHELL_BANNER, 14);
		free(line);
	}
	return 0;
}
