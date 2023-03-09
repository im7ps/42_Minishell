/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:34 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/09 20:24:19 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_delete_node(t_list **list, t_list *nodeToDelete) 
{
	t_list *prevNode;

    // Se la lista è vuota o il nodo da eliminare è nullo, non fare nulla
    if (*list == NULL || nodeToDelete == NULL) {
        return;
    }
    
    // Se il nodo da eliminare è il primo della lista, modifica il puntatore alla testa della lista
    if (*list == nodeToDelete) {
        *list = nodeToDelete->next;
        free(nodeToDelete);
        return;
    }

    // Trova il nodo precedente a quello da eliminare
    prevNode = *list;
    while (prevNode->next != NULL && prevNode->next != nodeToDelete) {
        prevNode = prevNode->next;
    }
    
    // Se il nodo da eliminare non è presente nella lista, non fare nulla
    if (prevNode->next == NULL) {
        return;
    }
    
    // Modifica il puntatore "next" del nodo precedente in modo che punti al nodo successivo
    prevNode->next = nodeToDelete->next;
    free(nodeToDelete);
}

int	ft_unset(t_list *head, t_list **envp, char  *var)
{
	int		i;
	t_list	*env;

	i = 0;
    if (var != NULL)
    {
        env = *envp;
        while (env)
        {
            if (!(strncmp(var, env->key, ft_strlen(var))))
            {
                ft_delete_node(envp, env);
            }
            env = env->next;
        }
    }
    else if (head != NULL)
    {
        while (head->cmd_m[i])
        {
            env = *envp;
            while (env)
            {
                if (!(strncmp(head->cmd_m[i], env->key, ft_strlen(head->cmd_m[i]))))
                {
                    ft_delete_node(envp, env);
                }
                env = env->next;
            }
            i++;
        }
    }
	return (0);
}