/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:27:48 by vparekh           #+#    #+#             */
/*   Updated: 2020/02/05 15:10:42 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line.h"
# include "libft.h"
# include <signal.h>
# define SHELL_BANNER "minishell-1.0$"
# define EXIT_MSG "bye!\n"
# define CMD_EXIT "exit"
typedef		struct	s_minishell_meta
{
	char cmd;
}					t_minishell_meta;

t_minishell_meta			*init_minishell_meta(t_minishell_meta *ms);
void						parse(t_minishell_meta *ms, char *line);
void						process(t_minishell_meta *ms);
void						sig_int_handler(int sig);
void						ms_exit();
#endif
