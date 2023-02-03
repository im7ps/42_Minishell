/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/02/03 16:15:04 by sgerace          ###   ########.fr       */
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
	minip->exit_status = 0;

	return (minip);
}

void	ft_execute_mini(t_minishell **minip)
{
	if (signal(SIGINT, &ft_CTRL_C_handler) == SIG_ERR) {
		printf("failed to register interrupts with kernel\n");
	}
	signal(SIGQUIT, &ft_CTRL_S_handler);
	t_minishell *mini;
	
	mini = *minip;
	write(1, "here", 4);
	while (1)
	{
		mini->input = readline("minishell> ");
		if (mini->input == NULL)
			ft_CTRL_D_handler(3);
		add_history(mini->input);
		// if (ft_invalid_check(mini->input))
		// 	ft_strerr("Invalid char!\n");
		// if (ft_lexer(&mini))
		// 	return (1);
		free(mini->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (signal(SIGINT, &ft_CTRL_C_handler) == SIG_ERR) {
		printf("failed to register interrupts with kernel\n");
	}
	signal(SIGQUIT, &ft_CTRL_S_handler);
	t_minishell *mini;

	mini = (t_minishell *) malloc (sizeof(t_minishell));
	mini = ft_mini_constructor(&mini);
	mini = ft_get_mini(mini);
	ft_execute_mini(&mini);
	return (0);
}

