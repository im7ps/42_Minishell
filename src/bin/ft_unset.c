/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:20:33 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 11:19:18 by sgerace          ###   ########.fr       */
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

void	ft_handle_envp(t_list **envp, char *str)
{
	t_list	*env;

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

void	ft_handle_export(t_list **expp, char *str)
{
	t_list	*exp;

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

void	ft_find_node(t_list **envp, char *str, t_list **expp)
{
	if (envp != NULL)
	{
		ft_handle_envp(envp, str);
	}
	if (expp != NULL)
	{
		ft_handle_export(expp, str);
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
