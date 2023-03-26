/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:34 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/26 13:34:27 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void ft_delete_node(t_list **list, t_list *nodeToDelete) 
{
	t_list *prevNode;

    if (*list == NULL || nodeToDelete == NULL) 
        return;
    if (*list == nodeToDelete) 
	{
        *list = nodeToDelete->next;
        free(nodeToDelete);
        return;
    }
    prevNode = *list;
    while (prevNode->next != NULL && prevNode->next != nodeToDelete) 
	{
        prevNode = prevNode->next;
    }
    if (prevNode->next == NULL) 
        return;
    prevNode->next = nodeToDelete->next;
    free(nodeToDelete);
	nodeToDelete = NULL;
}

void	ft_find_node(t_list *head, t_list **envp, char  *str)
{
	t_list *env;
	
	env = *envp;
	while (env)
	{
		if (!(strncmp(str, env->key, ft_strlen(str))))
		{
			ft_delete_node(envp, env);
			break ;
		}
		env = env->next;
	}
}

int	ft_unset(t_list *head, t_list **envp, char  *var)
{
	int		i;

	i = 0;
	if (var != NULL)
	{
		ft_find_node(head, envp, var);
	}
    else if (head != NULL)
    {
        while (head->cmd_m[i])
        {
			ft_find_node(head, envp, head->cmd_m[i]);
			i++;
        }
    }
	return (0);
}