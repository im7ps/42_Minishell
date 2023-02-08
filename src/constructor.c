/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:46 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/08 12:52:27 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell *ft_mini_constructor(t_minishell **mini)
{
	t_minishell *minip;

	minip = *mini;
	minip->input = "Miao\n";
	minip->full_cmd = NULL;
	minip->cmd_list = NULL;
	minip->envp_list = NULL;
	minip->exit_status = 0;

	return (minip);
}

t_minishell *ft_load_envp(t_minishell **minip, char **envp)
{
	t_minishell *mini;
	t_list 		*new_node;
	char		**split_ret;
	int			i;

	mini = *minip;
	i = 0;
	while (envp[i])
	{
		new_node = ft_malloc_stuff(NODE_NUM);
		split_ret = ft_split(envp[i], '=');
		new_node->key = split_ret[0];
		new_node->value = split_ret[1];
		new_node->next = NULL;
		ft_lstadd_back(&mini->envp_list, new_node);
		i++;
	}
	return (mini);
}
