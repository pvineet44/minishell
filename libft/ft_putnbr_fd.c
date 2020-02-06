/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:15:22 by vparekh           #+#    #+#             */
/*   Updated: 2019/10/11 15:45:03 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbr_len(int nbr)
{
	int		i;

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
	if (nbr == 0)
		return ("0");
	return ("-2147483648");
}

static void		ft_itoa2(int nbr, int fd)
{
	int		length;
	int		sig;
	int		i;
	char	result[15];

	i = 0;
	sig = 0;
	length = ft_nbr_len(nbr);
	if (nbr < 0)
		sig++;
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
	ft_putstr_fd(result, fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	if ((n == 0) || (n == -2147483648))
		ft_putstr_fd(preturn(n), fd);
	else
		ft_itoa2(n, fd);
}
