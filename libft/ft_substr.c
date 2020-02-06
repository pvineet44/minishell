/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:05:16 by vparekh           #+#    #+#             */
/*   Updated: 2019/10/10 16:31:34 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char				*substr;
	unsigned int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((unsigned)ft_strlen(s) < start)
		return (ft_calloc(1, sizeof(char)));
	substr = (char*)malloc((len * sizeof(char)) + 1);
	if (!substr)
		return (NULL);
	while (s[start] != '\0' && len > 0)
	{
		substr[i++] = s[start++];
		len--;
	}
	substr[i] = '\0';
	return (substr);
}
