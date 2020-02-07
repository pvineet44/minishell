/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:27:48 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/07 12:59:01 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line.h"
# include "libft.h"
# include <signal.h>
# define SHELL_BANNER "minishell-1.0$"
# define COMMAND_NOT_FOUND ": command not found\n"
# define EXIT_MSG "bye!\n"
# define CMD_EXIT "exit"
# define CMD_ECHO "echo"
# define CMD_PWD "pwd"
# define CMD_ENV "env"

typedef struct				s_minishell_meta
{
	char	cmd;
	char	**args;
	int		arg_start;
	char	*arg;
	int		opt_bit;
}					t_minishell_meta;

t_minishell_meta			*init_minishell_meta(t_minishell_meta *ms);
void						pre_parse(t_minishell_meta*ms, char *line);
void						parse(t_minishell_meta *ms, char *line);
void						process(t_minishell_meta *ms, char *line);
void						sig_int_handler(int sig);
void						ms_exit(t_minishell_meta *ms, char *line);
void						ms_pwd(t_minishell_meta *ms);
void						ms_env(t_minishell_meta *ms);
void						free_all(t_minishell_meta *ms, char *line);
#endif
