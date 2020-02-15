/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:20:04 by vparekh           #+#    #+#             */
/*   Updated: 2019/10/11 11:46:21 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_stradd(char *str, char ch)
{
	char		*res;
	int			len;
	int			i;

	res = NULL;
	len = str ? ft_strlen(str) : 0;
	len = len + 2;
	res = (char*)malloc(sizeof(char) * (len));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (str && str[++i])
		res[i] = str[i];
	res[len - 2] = ch;
	res[len - 1] = 0;
	free(str);
	return (res);
}

static	char	**ft_return_zero(char **result)
{
	result = (char**)malloc(sizeof(char*));
	if (result == NULL)
		return (NULL);
	result[0] = NULL;
	return (result);
}

static char		**ft_process_split(char **result, const char *s, int i, char c)
{
	char	*partition;
	int		j;

	j = 0;
	partition = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
			partition = ft_stradd(partition, s[i]);
		else if (s[i + 1] != c)
		{
			result[j] = (char*)malloc(sizeof(char)
				* (ft_strlen(partition) + 1));
			if (result[j] == NULL)
				return (NULL);
			result[j] = ft_memcpy(result[j], partition,
				ft_strlen(partition) + 1);
			j++;
			free(partition);
			partition = 0;
		}
	}
	result[j] = partition;
	result[++j] = 0;
	return (result);
}

static	char	**ft_pre_process_split(char **result, const char *s, char c)
{
	int			i;
	char		*partition;

	i = -1;
	partition = 0;
	while (s[++i] == c)
		;
	i--;
	return (ft_process_split(result, s, i, c));
}

char			**ft_split(const char *s, char c)
{
	char		**result;

	result = NULL;
	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
		return (ft_return_zero(result));
	result = (char**)malloc(sizeof(char*) + (ft_strlen(s) * sizeof(char*)));
	if (result == NULL)
		return (NULL);
	return (ft_pre_process_split(result, s, c));
}
