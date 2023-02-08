/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/02/08 12:52:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execute_mini(t_minishell **minip)
{
	t_minishell *mini;
	if (signal(SIGINT, &ft_CTRL_C_handler) == SIG_ERR)
		printf("failed to register interrupt\n");
	if (signal(SIGQUIT, &ft_CTRL_S_handler) == SIG_ERR)
		printf("failed to register quit\n");
	
	mini = *minip;
	while (1)
	{
		mini->input = readline("minishell> ");
		if (mini->input == NULL)
			ft_CTRL_D_handler(3);
		add_history(mini->input);
		if (ft_invalid_check(mini->input))
			ft_strerr("Invalid char!\n");
		if (ft_lexer(&mini))
			return ;
		int	i;
		mini = *minip;
		while (mini->cmd_list)
		{
			i = 0;
			while (mini->cmd_list->cmd_m[i])
			{
				printf("%s\n", mini->cmd_list->cmd_m[i]);
				i++;
			}
			mini->cmd_list = mini->cmd_list->next;
		}
		//free(mini->input); //SE IMPLEMENTO IL DOLLAR EXPANDER FREEARE L INPUT COME FACCIO DI SOLITO MANDA IN CRASH IL PROGRAMMA
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell *mini;
	if (signal(SIGINT, &ft_CTRL_C_handler) == SIG_ERR) 
		printf("failed to register interrupt\n");
	if (signal(SIGQUIT, &ft_CTRL_S_handler) == SIG_ERR)
		printf("failed to register quit\n");

	mini = (t_minishell *) malloc (sizeof(t_minishell));
	mini = ft_mini_constructor(&mini);
	mini = ft_get_mini(mini);
	ft_load_envp(&mini, envp);
	ft_execute_mini(&mini);
	return (0);
}

