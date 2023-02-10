/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/02/10 21:17:38 by sgerace          ###   ########.fr       */
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
	
	while (1)
	{
		mini->input = readline("minishell> ");
		if (mini->input == NULL)
			ft_CTRL_D_handler(3);
		/*if (ft_input_checker(mini->input) != 0)
		{
			ft_perror(ERR_INPUT, NULL);
			return ;
		}*/
		add_history(mini->input);
		if (ft_lexer(&mini, &flags))
			return ;
		//free(mini->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell *mini;
	t_miniflags	*miniflags;
	if (signal(SIGINT, &ft_CTRL_C_handler) == SIG_ERR) 
		printf("failed to register interrupt\n");
	if (signal(SIGQUIT, &ft_CTRL_S_handler) == SIG_ERR)
		printf("failed to register quit\n");

	mini = (t_minishell *) malloc (sizeof(t_minishell));
	miniflags = (t_miniflags *) malloc (sizeof(t_miniflags));
	mini = ft_mini_constructor(&mini, &miniflags, envp);
	ft_execute_mini(&mini, &miniflags);
	return (0);
}

