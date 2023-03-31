/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:41:37 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:49:05 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*prev;

	if (*lst == NULL)
		return ;
	else
	{
		while (*lst != NULL)
		{
			prev = *lst;
			*lst = (*lst)->next;
			del(prev->content);
			free(prev);
		}
	}
}
