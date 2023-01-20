/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/01/20 17:05:39 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	check_cmd(t_minishell *mini)
// {
// 	mini->full_cmd = ft_split(mini->input, ' ');
// 	if(builtin(mini))
// 		ft_perror(ERR_NCMD, mini->full_cmd[0]);
// }

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

	/*modificato condizione while da mini.exit_status == 0 a 1*/
	while (1)
	{
		mini.input = readline("minishell> ");
		add_history(mini.input);
		if (ft_lexer(&mini))
			return (1);
		//check_cmd(&mini);
	}
	return (0);
}
