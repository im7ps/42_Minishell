/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:33:46 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/18 20:18:37 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell	*ft_load_envp(t_minishell **minip, char **envp)
{
	t_minishell *mini;
	t_list 		*new_node;
	char		**split_ret;
	int			i;

	// i = 0;
	// while (envp[i])
	// {
	// 	ft_printf("Test %s\n", envp[i]);
	// 	i++;
	// }
	
	mini = *minip;
	i = 0;
	while (envp[i])
	{
		new_node = (t_list *) malloc (sizeof(t_list));
		if (new_node == NULL)
			return (NULL);
		split_ret = ft_old_split(envp[i], '=');
		new_node->key = ft_strdup(split_ret[0]);
		new_node->value = ft_strdup(split_ret[1]);
		new_node->start_red = 0;
		new_node->final_red = 0;
		new_node->red = 0;
		new_node->name = NULL;
		new_node->args = NULL;
		new_node->flags = NULL;
		new_node->end = NULL;
		new_node->next = NULL;
		ft_lstadd_back(&mini->envp_list, new_node);
		free_stuff(NULL, split_ret, NULL, NULL);
		// free(split_ret[0]);
		// free(split_ret[1]);
		i++;
	}
	return (mini);
}

t_minishell *ft_mini_constructor(t_minishell **mini, t_miniflags **miniflags, char **envp)
{
	t_minishell *minip;
	t_miniflags *minif;
	
	minif = *miniflags;
	minip = *mini;

	exit_status = 0;

	minip->input = NULL;
	minip->full_cmd = NULL;
	minip->cmd_list = NULL;
	minip->index = 0;
	minip->cmd_num = 0;
	minip->built_in_counter = 0;

	minip->envp_list = NULL;
	minip = ft_get_mini(minip);

	ft_load_envp(&minip, envp);

	minif->d_quote = false;
	minif->s_quote = false;
	minif->pipe = false;
	minif->red_i = false;
	minif->red_o = false;
	minif->read_i = false;
	minif->append_o = false;

	return (minip);
}
