/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:03:20 by vparekh           #+#    #+#             */
/*   Updated: 2019/10/11 11:47:35 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *s1, const char *s2, int n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j] && j < n)
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}

int			ft_strlcat(char *dst, const char *src, int dst_size)
{
	int	src_len;
	int	dest_len;

	src_len = ft_strlen((char *)src);
	dest_len = ft_strlen(dst);
	if (dest_len >= dst_size)
		return (dst_size + src_len);
	ft_strncat(dst, src, dst_size - dest_len - 1);
	return (dest_len + src_len);
}
