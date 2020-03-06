/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 15:53:48 by mashar            #+#    #+#             */
/*   Updated: 2020/02/09 17:02:52 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_unset_single(char **env, char *arg, char **path)
{
	int		env_len;
	int		var_len;
	int		i;

	i = -1;
	if (!check_var(arg, "unset"))
		return ;
	var_len = ft_strlen(arg);
	while (env[++i] != '\0')
	{
		env_len = 0;
		while (env[i][env_len] != '=')
			env_len++;
		if (var_len != env_len)
			continue;
		if (ft_strncmp(arg, env[i], var_len) != 0)
			continue;
		while (env[++i] != 0)
			env[i - 1] = env[i];
		env[--i] = 0;
		break ;
	}
	if (ft_strcmp(arg, "PATH") == 0)
		free_tab(path);
}


void	ms_unset(char **env, char **args, char **path)
{
	int	i;

	i = 0;
	errno = 0;
	while (args[i] != 0)
	{
		ms_unset_single(env, args[i], path);
		i++;
	}
}