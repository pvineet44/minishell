/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:20:14 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/09 15:49:57 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			check_args(char **args)
{
	while (*args)
	{
		ft_putendl_fd(*args, STDOUT_FILENO);
		args++;
	}
}

void			init_ms(t_minishell_meta *ms)
{
	ms->arg_start = 0;
	ms->process_bit = 0;
	ms->arg = 0;
	ms->file_fd = -1;
	ms->out_fd = -1;
	ms->in_fd = -1;
	ms->multiline = 0;
}

void			invoke_minishell(t_minishell_meta *ms, char *line)
{
	int 	i;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim(line, "\t \n\v\f\r");
	ft_free(&line);
	line = ft_strdup(tmp);
	ft_free(&tmp);
	init_ms(ms);
	parse(ms, line);
	if (!ms->multiline && line[0] != '\0')
	{
		process(ms, line);
		free_all(ms, line);
	}
	write(STDOUT_FILENO, SHELL_BANNER, 14);
}

void			set_path(t_minishell_meta *ms)
{
	ms->arg = 0;
	substitute_value("$PATH", 0, ms);
	ms->path = ft_split(ms->arg, ':');
	ft_free(&ms->arg);
}

int				main(int ac, char **av, char **env)
{
	char				*line;
	t_minishell_meta	*ms;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	if (!(ms = malloc(sizeof(t_minishell_meta))))
		return (0);
	ms->env = env;
	set_path(ms);
	line = NULL;
	write(STDOUT_FILENO, SHELL_BANNER, 14);
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
		{
			write(STDOUT_FILENO, SHELL_BANNER, 14);
			free(line);
			continue ;
		}
		invoke_minishell(ms, line);
	}
	free(ms);
	return (0);
}
