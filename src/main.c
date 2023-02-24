/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/02/24 21:04:38 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_clean_all(t_minishell **minip, t_miniflags **minif)
{
	t_minishell *mini;
	t_miniflags *flags;

	mini = *minip;
	flags = *minif;
	free_stuff(NULL, NULL, &mini->envp_list, flags);
	free_stuff(NULL, NULL, &mini->cmd_list, NULL);
	free_stuff(NULL, NULL, &mini->envp_list, NULL);
}

void	ft_execute_mini(t_minishell **minip, t_miniflags **minif)
{
	t_minishell *mini;
	t_miniflags *flags;
	int			cmd_num;

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
			ft_printf("Error: l'input non può essere nullo\n");
			free_stuff(NULL, NULL, &mini->envp_list, flags);
			ft_CTRL_D_handler(0);
		}
		else if (!(ft_strncmp(mini->input, "exit", 4)))
		{
			ft_printf("Caricamento procedura d'uscita in corso, non spegnere il computer\n");
			sleep(1);
			exit(1);
		}
		if (ft_input_checker(mini->input) != 0)
		{
			ft_printf("Error: è stata scritta qualche cagata astronomica\n");
			ft_perror(ERR_INPUT, NULL);
		}
		add_history(mini->input);
		if (ft_parser(&mini, &flags))
		{
			ft_printf("Error: parser fallito\n");
			free_stuff(NULL, NULL, &mini->envp_list, flags);
			free_stuff(NULL, NULL, &mini->cmd_list, NULL);
			exit(1);
		}
		cmd_num = ft_count_commands(&mini->cmd_list);
		ft_start_executing(&mini->cmd_list, cmd_num, &mini->envp_list);
		ft_lst_delete(&mini->cmd_list);
		
		/*int i = 0;
		while (mini->cmd_list)
		{
			ft_printf("%s\n", mini->cmd_list->cmd_m[1]);
			mini->cmd_list = mini->cmd_list->next;
			i++;
		}
		ft_printf("Num cmd: %d\n", i);*/
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

	//free_stuff(NULL, NULL, &mini->envp_list, NULL);
	//free(mini);
	//free(miniflags);
	return (0);
}

