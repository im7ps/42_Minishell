/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/02/17 20:54:25 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execute_mini(t_minishell **minip, t_miniflags **minif)
{
	t_minishell *mini;
	t_miniflags *flags;

	mini = *minip;
	flags = *minif;
	if (signal(SIGINT, &ft_CTRL_C_handler) == SIG_ERR)
		printf("failed to register interrupt\n");
	if (signal(SIGQUIT, &ft_CTRL_S_handler) == SIG_ERR)
		printf("failed to register quit\n");
	
	while (exit_status == 0)
	{
		mini->input = readline("minishell> ");
		if (mini->input == NULL)
		{
			free_stuff(NULL, NULL, &mini->envp_list, flags);
			ft_CTRL_D_handler(0);
		}
		if (ft_input_checker(mini->input) != 0)
		{
			ft_perror(ERR_INPUT, NULL);
		}
		add_history(mini->input);
		if (ft_parser(&mini, &flags))
		{
			free_stuff(NULL, NULL, &mini->envp_list, flags);
			free_stuff(NULL, NULL, &mini->cmd_list, NULL);
			exit(0);
		}
		ft_start_executing(&mini->cmd_list);

		// int i;
		// while (mini->cmd_list)
		// {
		// 	i = 0;
		// 	while (mini->cmd_list->cmd_m[i])
		// 	{
		// 		ft_printf("%s\n", mini->cmd_list->cmd_m[i]);
		// 		i++;
		// 	}
		// 	mini->cmd_list = mini->cmd_list->next;
		// }

		free(mini->input);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell *mini;
	t_miniflags	*miniflags;
	if (signal(SIGINT, &ft_CTRL_C_handler) == SIG_ERR) 
		ft_printf("failed to register interrupt\n");
	if (signal(SIGQUIT, &ft_CTRL_S_handler) == SIG_ERR)
		ft_printf("failed to register quit\n");

	mini = (t_minishell *) malloc (sizeof(t_minishell));
	miniflags = (t_miniflags *) malloc (sizeof(t_miniflags));
	mini = ft_mini_constructor(&mini, &miniflags, envp);
	ft_execute_mini(&mini, &miniflags);
	return (0);
}

