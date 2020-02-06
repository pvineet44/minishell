/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:53:00 by vparekh           #+#    #+#             */
/*   Updated: 2019/10/11 11:47:14 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*strj;

	i = -1;
	j = -1;
	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
		return (ft_strdup(s1));
	strj = (char*)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!strj)
		return (0);
	while (s1[++i] != '\0')
		strj[i] = s1[i];
	while (s2[++j] != '\0')
	{
		strj[i] = s2[j];
		i++;
	}
	strj[i] = '\0';
	return (strj);
}
