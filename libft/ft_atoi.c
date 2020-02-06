/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:16:27 by vparekh           #+#    #+#             */
/*   Updated: 2019/10/10 19:16:39 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *s1)
{
	int					neg;
	unsigned long int	val;
	int					i;

	neg = 1;
	val = 0;
	i = 0;
	while ((s1[i] >= 9 && s1[i] <= 13) || s1[i] == 32)
		i++;
	if (s1[i] == '-')
		neg = -1;
	if (s1[i] == '-' || s1[i] == '+')
		i++;
	while ((ft_isdigit(s1[i])) && s1[i] != '\0')
		val = val * 10 + ((const char)s1[i++] - '0');
	return (val * neg);
}
