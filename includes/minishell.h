/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:27:48 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/09 17:10:31 by mashar           ###   ########.fr       */
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
# define CMD_UNSET "unset"
# define CMD_EXPORT "export"

typedef	struct				s_piped_minishell_meta
{
	char	**cmds;
	char	**args;
	char	*options;
}							t_piped_minishell_meta;

typedef struct				s_minishell_meta
{
	char					**args;
	int						arg_start;
	char					*arg;
	int						arg_bit;
	int						opt_bit;
	int						process_bit;
	char					**env;
	t_piped_minishell_meta	*piped_cmds;
}							t_minishell_meta;

void						check_args(char **args);
void						parse1(t_minishell_meta *ms, char *line);
void						process1(t_minishell_meta *ms);
void						sig_int_handler(int sig);
void						ms_exit(t_minishell_meta *ms, char *line);
void						ms_unset(t_minishell_meta *ms);
void						ms_export(t_minishell_meta *ms);
void						ms_pwd1();
void						ms_exit1(t_minishell_meta *ms);
void						ms_pwd();
void						ms_env(char	**env);
void						ms_echo(t_minishell_meta *ms);
void						free_all(t_minishell_meta *ms, char *line);
void						free_all1(t_minishell_meta *ms);
void						free_tab(char **args);
void						command_not_found(char *command);
void						init_ms(t_minishell_meta *ms);
int							parse_quotes(char *line, int i,
							t_minishell_meta *ms);
int							substitute_value(char *line, int i,
							t_minishell_meta *ms);


#endif
