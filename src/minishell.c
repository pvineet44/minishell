/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:20:14 by vparekh           #+#    #+#             */
/*   Updated: 2020/04/10 11:31:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			check_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd("|\n", 2);
		i++;
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
	ms->piped_cmds = 0;
	ms->no_args = 0;
	ms->path = 0;
	ms->n = 0;
	set_path(ms);
}

void			invoke_minishell(t_minishell_meta *ms, char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, "\t \n\v\f\r");
	ft_free(&line);
	line = ft_strdup(tmp);
	ft_free(&tmp);
	init_ms(ms);
	line = parse(ms, line);
	if (!ms->multiline && line[0] != '\0')
	{
		process(ms, line);
		free_all(ms, line);
	}
	else
		free_all(ms, line);
	write(STDOUT_FILENO, SHELL_BANNER, 15);
}

int				is_spaces_only(char *line)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int				main(int ac, char **av, char **env)
{
	char				*line;
	t_minishell_meta	*ms;

	(void)ac;
	(void)av;
	line = NULL;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	if (!(ms = malloc(sizeof(t_minishell_meta))))
		return (1);
	set_env_export(ms, env);
	while (1)
	{
		if (get_line(&line, ms))
			continue ;
		if ((line[0] == '\0' || is_spaces_only(line)) && ft_free(&line))
		{
			write(STDOUT_FILENO, SHELL_BANNER, 15);
			continue ;
		}
		invoke_minishell(ms, line);
	}
	free_tab(ms->path);
	free(ms);
	return (0);
}
