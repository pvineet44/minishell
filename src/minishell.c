/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:20:14 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/05 14:22:42 by vparekh          ###   ########.fr       */
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
	ms = init_minishell_meta(ms);
	fd = 0;
	line = NULL;
	write(1, SHELL_BANNER, 14);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'x')
		{
			write(1, EXIT_MSG, 5);
			break;
		}
		write(1, SHELL_BANNER, 14);
	}
	return 0;
}
