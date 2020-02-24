/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:27:48 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/15 17:10:23 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line.h"
# include "libft.h"
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# define SHELL_BANNER "minishell-1.0$"
# define SHELL_NAME "minishell-1.0"
# define COMMAND_NOT_FOUND ": command not found\n"
# define EXIT_MSG "bye!\n"
# define CMD_EXIT "exit"
# define CMD_ECHO "echo"
# define CMD_PWD "pwd"
# define CMD_ENV "env"
# define CMD_UNSET "unset"
# define CMD_EXPORT "export"
# define CMD_CD "cd"

typedef	struct				s_piped_minishell_meta
{
	char	**cmds;
	char	**args;
	char	*options;
	char	**files;
}							t_piped_minishell_meta;

typedef struct				s_minishell_meta
{
	int						arg_start;
	char					*arg;
	int						process_bit;
	char					**env;
	int						in_fd;
	int						out_fd;
	int						file_fd;
	int						multiline;
	int						end_quote;
	t_piped_minishell_meta	*piped_cmds;
}							t_minishell_meta;
t_piped_minishell_meta		*init_cmds(int length);
char						*get_command(char *command, char *line,
							t_minishell_meta *ms);
void						check_args(char **args);
void						parse(t_minishell_meta *ms, char *line);
void						parse_piped_commands(t_minishell_meta *ms,
							char *line, char d);
void						process(t_minishell_meta *ms, char *line);
void						sig_int_handler(int sig);
void						sig_quit_handler(int sig);
int							get_exit_status(t_minishell_meta *ms);
void						ms_exit(t_minishell_meta *ms, char *line);
void						ms_unset(char **env, char *arg);
void						ms_export(char **env, char *arg);
void						ms_pwd();
void						ms_env(char	**env);
void						ms_echo(char *arg);
void						ms_execute(char *path, char *args, char **env);
void						free_tab(char **args);
void						free_all(t_minishell_meta *ms, char *line);
void						command_not_found(char *command);
void						init_ms(t_minishell_meta *ms);
void						unset_fd(t_minishell_meta *ms);
void						handle_fd(char *line, t_minishell_meta *ms,
							int index);
void						ms_cd(char *path);
int							parse_quotes(char *line, int i,
							t_minishell_meta *ms);
int							substitute_value(char *line, int i,
							t_minishell_meta *ms);
int							ft_isredir(char c);
char						*get_redir(char *redir, char *line,
							t_minishell_meta *ms);
char						*get_file(char *file, char *line,
							t_minishell_meta *ms);
char						*parse_input_line(char *line, t_minishell_meta *ms);
char						*replace_semi(char *line, int i, char quote,\
							t_minishell_meta *ms);

#endif
