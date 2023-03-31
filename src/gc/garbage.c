/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 21:37:49 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:38:04 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_node(t_garbage **head, void *ptr)
{
	t_garbage	*new_node;

	new_node = (t_garbage *) malloc (sizeof (t_garbage));
	new_node->ptr = ptr;
	new_node->next = *head;
	*head = new_node;
}

void	*gc_alloc(t_garbage **head, int size, int count)
{
	void	*ptr;

	ptr = malloc (size);
	if (count != 0)
	{
		ft_bzero(ptr, count);
	}
	add_node(head, ptr);
	return (ptr);
}

void	ft_garbage_collector(t_garbage *head)
{
	t_garbage	*temp;

	temp = NULL;
	while (head != NULL)
	{
		free(head->ptr);
		temp = head;
		head = head->next;
		free(temp);
	}
}
