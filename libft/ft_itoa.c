/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:52:25 by vparekh           #+#    #+#             */
/*   Updated: 2019/10/11 11:12:01 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbr_len(int nbr)
{
	int		i;

	if (nbr == 0)
		return (1);
	i = 0;
	if (nbr < 0)
		nbr = -nbr;
	while (nbr > 0)
	{
		nbr = (nbr / 10);
		i++;
	}
	return (i);
}

static char		*preturn(int nbr)
{
	int		size;

	if (nbr == 0)
		size = 2;
	else
		size = 12;
	if (size == 12)
		return (ft_strdup("-2147483648"));
	return (ft_strdup("0"));
}

char			*ft_itoa(int nbr)
{
	int		length;
	int		sig;
	int		i;
	char	*result;

	i = 0;
	sig = nbr < 0 ? 1 : 0;
	length = ft_nbr_len(nbr);
	if ((nbr == 0) || (nbr == -2147483648))
		return (preturn(nbr));
	if (!(result = (char *)malloc(sizeof(char) * (length + 1 + sig))))
		return (NULL);
	if (sig)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (++i <= length)
	{
		result[length + sig - i] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	result[length + sig] = '\0';
	return (result);
}
