/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:30:22 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/06 19:14:50 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*tmp;

	tmp = lst;
	if (lst != NULL)
	{
		lst = tmp->next;	//andiamo al prossimo nodo
		del(tmp->content);	//eliminiamo il contenuto del nodo precedente
		free(tmp);			//SEMPRE FARE LA FREEEEEE
	}
}
