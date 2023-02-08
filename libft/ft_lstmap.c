/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:57:16 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Iterates the list ’lst’ and applies the function
// ’f’ on the content of each node. Creates a new
// list resulting of the successive applications of
// the function ’f’. The ’del’ function is used to
// delete the content of a node if needed.
// source: 42libft subject 03/2022

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
		current_node = ft_lstnew((*f)(lst->content));  //crea una nuova lista con i nodi della vecchia a cui e' stata applicata la funzione (f)
		if (current_node == NULL)
		{
			ft_lstclear(&f_list, (*del));				//anche se il subject cita "the content of a node" questo script elimina tutta la nuova lista usando l'indirizzo di f_list, almeno credo, e ritorna NULL
			return (NULL);
		}
		ft_lstadd_back(&f_list, current_node);
		lst = lst->next;
	}
	return (f_list);
}
