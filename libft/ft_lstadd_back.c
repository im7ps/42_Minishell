/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:22:22 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/07 18:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//aggiunge un nodo alla fine della lista

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp_l;

	if (*lst == NULL)			//se la lista punta a NULL e' una lista vuota, facciamola puntare a new e l'avremo aggiunto "in fondo"
		*lst = new;
	else
	{
		tmp_l = ft_lstlast(*lst);		//tmp_l punta all ultimo elemento non nullo
		tmp_l->next = new;			//settiamo new come il nuovo ultimo nodo modificando il nodo puntato da tmp_l
	}
}
