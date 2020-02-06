/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparekh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:16:00 by vparekh           #+#    #+#             */
/*   Updated: 2019/10/11 20:10:11 by vparekh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	if (!(list = malloc(sizeof(t_list))))
		return (0);
	if (list)
	{
		list->content = (void *)malloc(sizeof(void *));
		if (list->content == NULL)
			return (NULL);
		list->content = content;
		list->next = 0;
	}
	return (list);
}
