/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:42:02 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/06 19:12:21 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nodo;

	nodo = (t_list *) malloc (sizeof(t_list));		//crea un nuovo nodo, come grandezza per l area di memoria da allocare usiamo la grandezza della struttura
	if (nodo == NULL)
		return (NULL);
	nodo->content = content;						//inserisce il contenuto desiderato nel nodo
	nodo->next = NULL;								//e' un solo nodo, quindi inizializzato a NULL
	return (nodo);
}
