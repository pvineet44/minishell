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
	int i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 2);
			ft_putstr_fd("|\n",2);
		i++;
	}
}

void            set_export(t_minishell_meta *ms)
{
    int i;
    int env_len;

    i = 0;
	env_len = 0;
    while (ms->env[env_len] != 0)
        env_len++;
    ms->export = (char**)malloc(sizeof(char*) * (env_len + 1));
    if(ms->export == NULL)
        exit(0); //Properly exit here
    ms->export[i] = 0;
    return ;

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
	set_path(ms);
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

void			set_path(t_minishell_meta *ms)
{
	ms->arg = 0;
	substitute_value("$PATH", 0, ms);
	if (ms->path != 0)
	{
		free(ms->path);
		ms->path = 0;
	}
	ms->path = ft_split(ms->arg, ':');
	ft_free(&ms->arg);
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
	char				*tmp_line;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	if (!(ms = malloc(sizeof(t_minishell_meta))))
		return (0);
	ms->env = env;
    set_export(ms);
	ms->path = 0;
	tmp_line = NULL;
	line = NULL;
	write(STDOUT_FILENO, SHELL_BANNER, 15);
	while (1)
	{
		if (get_line(&line,ms))
			continue ;
		if (line[0] == '\0' || is_spaces_only(line))
		{
			write(STDOUT_FILENO, SHELL_BANNER, 15);
			ft_free(&line);
			continue ;
		}
		invoke_minishell(ms, line);
	}
	free_tab(ms->path);
	free(ms);
	return (0);
}
