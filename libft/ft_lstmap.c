/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:57:16 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:48:42 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*f_list;
	t_list	*current_node;

	if (lst == NULL)
		return (lst);
	f_list = NULL;
	while (lst != NULL)
	{
		current_node = ft_lstnew((*f)(lst->content));
		if (current_node == NULL)
		{
			ft_lstclear(&f_list, (*del));
			return (NULL);
		}
		ft_lstadd_back(&f_list, current_node);
		lst = lst->next;
	}
	return (f_list);
}
