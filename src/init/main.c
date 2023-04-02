/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/04/02 12:41:50 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

void	ft_print_list(t_list **headp)
{
	t_list	*head;

	head = *headp;
	while (head)
	{
		ft_printf("%p\n", head);
		head = head->next;
	}
}

void	ft_execute_mini(t_minishell **minip, char **envp)
{
	t_minishell	*mini;

	if (signal(SIGQUIT, &ft_ctrl_d_handler) == SIG_ERR)
		printf("failed to register quit\n");
	if (signal(SIGINT, &ft_ctrl_c_handler) == SIG_ERR)
		printf("failed to register interrupt\n");
	mini = *minip;
	while (1)
	{
		mini->input = readline("minishell> ");
		if (mini->input == NULL)
		{
			ft_ctrl_d_handler(0);
			return ;
		}
		if (ft_input_checklist(minip, &(*minip)->envp_list) == 1)
			return ;
		add_history(mini->input);
		if (ft_parser(minip))
			return ;
		ft_start_executing(&mini, &mini->envp_list);
		ft_mini_initializer(&mini, envp, 0);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	(void)argc;
	(void)argv;
	if (signal(SIGINT, &ft_ctrl_c_handler) == SIG_ERR)
		ft_printf("failed to register interrupt\n");
	if (signal(SIGQUIT, &ft_ctrl_s_handler) == SIG_ERR)
		ft_printf("failed to register quit\n");
	mini = (t_minishell *) malloc (sizeof(t_minishell));
	ft_mini_initializer(&mini, envp, 1);
	ft_execute_mini(&mini, envp);
	ft_printf("Fine programma\n");
	ft_garbage_collector(mini->garbage);
	free(mini);
	return (0);
}
