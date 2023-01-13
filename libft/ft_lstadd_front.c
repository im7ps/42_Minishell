/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:50:03 by sgerace           #+#    #+#             */
/*   Updated: 2022/04/06 19:03:37 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//aggiunge un nodo all inizio di una lista

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = (*lst);
	(*lst) = new;
}
