/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:20:14 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 14:25:21 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			check_args(char **args)
{
	char nl;

	nl = 10;
	while (*args)
	{
		write(1, *args, ft_strlen(*args));
		write(1, &nl, 1);
		args++;
	}
}

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
		if(line[0] == '\0')
		{
			write(1, SHELL_BANNER, 14);
			free(line);
			continue ;
		}
		ms = init_minishell_meta(ms);
		pre_parse(ms, line);
//		check_args(ms->args);
		parse(ms, line);
		process(ms, line);
		write(1, SHELL_BANNER, 14);
		free_all(ms, line);
	}
	free(ms);
	return 0;
}
