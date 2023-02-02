/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/02/02 13:34:01 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	check_cmd(t_minishell *mini)
// {
// 	mini->full_cmd = ft_split(mini->input, ' ');
// 	if(builtin(mini))
// 		ft_perror(ERR_NCMD, mini->full_cmd[0]);
// }

void	ft_CTRL_C_handler(int signum)
{
	t_minishell	mini;
	
	printf("\n");
	while (1)
	{
		mini.input = readline("minishellz> ");
		add_history(mini.input);
		if (ft_lexer(&mini))
			return ;
	}
}

void	ft_CTRL_D_handler(int signum)
{
	
}

void	ft_CTRL_S_handler(int signum)
{
	
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

	signal(SIGINT, ft_CTRL_C_handler);
	//signal(SIGINT, ft_CTRL_D_handler);
	//signal(SIGINT, ft_CTRL_S_handler);

	/*modificato condizione while da mini.exit_status == 0 a 1*/
	while (1)
	{
		mini.input = readline("minishell> ");
		add_history(mini.input);
		// if (ft_lexer(&mini))
		// 	return (1);
		//check_cmd(&mini);
	}
	return (0);
}

