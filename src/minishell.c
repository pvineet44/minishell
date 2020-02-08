/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:20:14 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/08 15:19:40 by mashar           ###   ########.fr       */
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

void			init_ms(t_minishell_meta *ms)
{
	ms->arg_bit = 0;
	ms->opt_bit = 0;
	ms->arg_start = 0;
	ms->process_bit = 0;
	ms->arg = 0;
	ms->cmd = 0;
}

void			invoke_minishell(t_minishell_meta *ms, char *line)
{
	int i;

	i = 0;
	init_ms(ms);
	pre_parse(ms, line);
	while (ms->args[i])
	{
		init_ms(ms);
		parse(ms, ms->args[i]);
		if (ms->process_bit != -1)
			process(ms, line);
		i++;
	}
	write(1, SHELL_BANNER, 14);
	free_all(ms, line);
}

int				main(int ac, char **av, char **env)
{
	char				*line;
	t_minishell_meta	*ms;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_int_handler);
	if (!(ms = malloc(sizeof(t_minishell_meta))))
		return (0);
	ms->env = env;
	line = NULL;
	write(1, SHELL_BANNER, 14);
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
		{
			write(1, SHELL_BANNER, 14);
			free(line);
			continue ;
		}
		invoke_minishell(ms, line);
	}
	free(ms);
	return (0);
}
