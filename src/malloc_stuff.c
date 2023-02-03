/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:32:53 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/03 18:17:39 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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