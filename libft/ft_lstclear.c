/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:41:37 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Deletes and frees the given node and every
// successor of that node, using the function ’del’
// and free.
// source: 42libft subject 03/2022

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
			prev = *lst;			//stesso ragionamento di swap, copi il riferimento del nodo da eliminare, vai al prossimo e POI elimini il nodo precedente, grazie al riferimento stai eliminando l originale e non una copia
			*lst = (*lst)->next;
			del(prev->content);
			free(prev);
		}
	}
}
