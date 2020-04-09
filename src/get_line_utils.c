/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <mashar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 18:11:07 by mashar            #+#    #+#             */
/*   Updated: 2020/04/09 18:15:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void			check_ret_lt_zero(int *ret, char *new_line,\
char **line, t_minishell_meta *ms)
{
	(void)new_line;
	if (*ret < 0)
	{
		ft_free(line);
		free_tab(ms->env);
		free_tab(ms->export);
		free(ms);
		exit(0);
	}
}

void			check_ret_eq_zero(int *ret, char *new_line,\
char *bef_line, t_minishell_meta *ms)
{
	if (*ret == 0 && errno == 1 && !ft_strlen(new_line))
	{
		ft_free(&bef_line);
		ft_free(&new_line);
		ft_putendl_fd(" exit", 1);
		free_tab(ms->env);
		free_tab(ms->export);
		free(ms);
		exit(0);
	}
}

void			check_ret_and_line(int *ret, char **line,\
t_minishell_meta *ms)
{
	if (*ret == 0 && !ft_strlen(*line))
	{
		ft_free(line);
		ft_putendl_fd(" exit", 1);
		free_tab(ms->export);
		free_tab(ms->env);
		free(ms);
		exit(0);
	}
}

void			errno_ne_one(char **line, char *bef_line,\
char *new_line)
{
	*line = ft_strjoin(bef_line, new_line);
	free(bef_line);
	free(new_line);
}

void			errno_eq_one(char **line, char *new_line)
{
	ft_free(line);
	*line = ft_strdup(new_line);
	ft_free(&new_line);
}
