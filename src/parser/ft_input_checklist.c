/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_checklist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:38:13 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 13:12:53 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_check_path(t_minishell **minip, t_list **envp)
{
	t_list		*env;
	t_minishell	*mini;

	mini = *minip;
	env = *envp;
	while (env != NULL)
	{
		if (!(ft_strncmp(env->key, "PATH", 5)))
		{
			mini->nopath = 0;
			return ;
		}
		env = env->next;
	}
	mini->nopath = 1;
	return ;
}

int	ft_input_checklist(t_minishell **minip, t_list **envp)
{
	t_minishell	*mini;

	mini = *minip;
	ft_check_path(minip, envp);
	if (!ft_handle_shllv(minip))
	{
		return (1);
	}
	if (ft_input_checker(mini->input, true) != 0)
	{
		ft_printf("Input error\n");
		return (1);
	}
	return (0);
}
