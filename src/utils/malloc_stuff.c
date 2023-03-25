/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:32:53 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/24 19:00:40 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    *ft_malloc_stuff(int n)
{
    t_list *node;
    if (n == NODE_NUM)
    {
        node = (t_list *)malloc(sizeof(t_list));
        return (node);
    }
    return (NULL);
}