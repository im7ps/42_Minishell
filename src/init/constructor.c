/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:46 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 14:41:21 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_initialize_newnode(t_list *new_node)
{
	new_node->name = NULL;
	new_node->args = NULL;
	new_node->flags = NULL;
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->next = NULL;
}

void	ft_envp_initialize(t_list *new_node)
{
	new_node->start_red = 0;
	new_node->final_red = 0;
	new_node->name = NULL;
	new_node->args = NULL;
	new_node->flags = NULL;
	new_node->end = NULL;
	new_node->next = NULL;
}

t_minishell	*ft_load_export(t_minishell **minip, char **envp)
{
	t_minishell	*mini;
	t_list		*new_node;
	char		**split_ret;
	int			i;

	mini = *minip;
	i = 0;
	while (envp[i])
	{
		new_node = gc_alloc(&mini->garbage, sizeof(t_list), 0);
		if (new_node == NULL)
			return (NULL);
		split_ret = ft_old_split(minip, envp[i], '=');
		new_node->key = ft_strdup_m(&mini->garbage, split_ret[0]);
		new_node->value = ft_strdup_m(&mini->garbage, split_ret[1]);
		ft_envp_initialize(new_node);
		ft_lstadd_back(&mini->export_list, new_node);
		i++;
	}
	return (mini);
}

t_minishell	*ft_load_envp(t_minishell **minip, char **envp)
{
	t_minishell	*mini;
	t_list		*new_node;
	char		**split_ret;
	int			i;

	mini = *minip;
	i = 0;
	while (envp[i])
	{
		new_node = gc_alloc(&mini->garbage, sizeof(t_list), 0);
		if (new_node == NULL)
			return (NULL);
		split_ret = ft_old_split(minip, envp[i], '=');
		new_node->key = ft_strdup_m(&mini->garbage, split_ret[0]);
		new_node->value = ft_strdup_m(&mini->garbage, split_ret[1]);
		ft_envp_initialize(new_node);
		ft_lstadd_back(&mini->envp_list, new_node);
		i++;
	}
	return (mini);
}

void	ft_mini_initializer(t_minishell **mini, char **envp, int flag)
{
	t_minishell	*minip;

	minip = *mini;
	minip->input = NULL;
	minip->full_cmd = NULL;
	minip->cmd_list = NULL;
	minip->index = 0;
	minip->cmd_num = 0;
	minip->built_in_counter = 0;
	minip->flush = 0;
	minip->nopath = 0;
	if (flag != 0)
	{
		minip->garbage = NULL;
		minip->envp_list = NULL;
		minip->export_list = NULL;
		ft_load_envp(&minip, envp);
		ft_load_export(&minip, envp);
	}
	return ;
}
