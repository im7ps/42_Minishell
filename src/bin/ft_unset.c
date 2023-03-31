/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:20:33 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 20:22:04 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_delete_node(t_list **list, t_list *node_to_delete)
{
	t_list	*prev_node;

	if (*list == NULL || node_to_delete == NULL)
		return ;
	if (*list == node_to_delete)
	{
		*list = node_to_delete->next;
		return ;
	}
	prev_node = *list;
	while (prev_node->next != NULL && prev_node->next != node_to_delete)
	{
		prev_node = prev_node->next;
	}
	if (prev_node->next == NULL)
		return ;
	prev_node->next = node_to_delete->next;
	node_to_delete = NULL;
}

void	ft_find_node(t_list **envp, char *str, t_list **expp)
{
	t_list	*env;
	t_list	*exp;

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
	exp = *expp;
	while (exp)
	{
		if (!(strncmp(str, exp->key, ft_strlen(str))))
		{
			ft_delete_node(expp, exp);
			break ;
		}
		exp = exp->next;
	}
}

int	ft_unset(t_list *head, t_list **envp, char *var, t_list **expp)
{
	int		i;

	i = 0;
	if (var != NULL)
	{
		ft_find_node(envp, var, expp);
	}
	else if (head != NULL)
	{
		while (head->cmd_m[i])
		{
			ft_find_node(envp, head->cmd_m[i], expp);
			i++;
		}
	}
	return (0);
}
