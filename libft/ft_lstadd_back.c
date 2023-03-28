/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:22:22 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/28 18:07:27 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//aggiunge un nodo alla fine della lista

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp_l;

	if (*lst == NULL) {
		*lst = new;
		new->prev = NULL; // il nuovo nodo non ha un nodo precedente
	}
	else
	{
		tmp_l = ft_lstlast(*lst);
		tmp_l->next = new;
		new->prev = tmp_l; // il nodo precedente del nuovo nodo è tmp_l
	}
}
