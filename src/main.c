/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/03/22 18:32:44 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status;

void	ft_execute_mini(t_minishell **minip, t_miniflags **minif)
{
	t_minishell *mini;
	t_miniflags *flags;
	t_list		*tmp;
	int			cmd_num;

	mini = *minip;
	flags = *minif;
	if (signal(SIGINT, &ft_CTRL_C_handler) == SIG_ERR)
		printf("failed to register interrupt\n");
	if (signal(SIGQUIT, &ft_CTRL_S_handler) == SIG_ERR)
		printf("failed to register quit\n");

	while (1)
	{
		mini->input = readline("minishell> ");
		//mini->input = "echo '$PWD' | cat -e";
		if (mini->input == NULL)
		{
			ft_printf("Error: l'input non può essere nullo\n");
			ft_lst_delete(&mini->envp_list);
			//free(mini);
			//free(flags);
			ft_CTRL_D_handler(0);
		}
		else if (!(ft_strncmp(mini->input, "exit", 4)))
		{
			ft_printf("Caricamento procedura d'uscita in corso, non spegnere il computer\n");
			ft_lst_delete(&mini->envp_list);
			//free(mini);
			//free(flags);
			exit(1);
		}
		if (ft_input_checker(mini->input) != 0)
		{
			ft_printf("Error: è stata scritta qualche cagata astronomica\n");
			ft_perror(ERR_INPUT, NULL);
			return ;
		}
		add_history(mini->input);
		if (ft_parser(&mini, &flags))
		{
			ft_printf("Error: parser fallito\n");
			//free_stuff(NULL, NULL, &mini->envp_list, flags);
			//free_stuff(NULL, NULL, &mini->cmd_list, NULL);
			exit(1);
		}
		tmp = mini->cmd_list;

		//inizializza variabile contenente numero dei comandi
		mini->cmd_num = ft_count_commands(&mini->cmd_list);
		//inizializza le flag redirection in ogni nodo della lista, settando red di partenza e di fine argomento della pipeline
		ft_upload_redirection(&mini->cmd_list);

		// t_list *env = mini->envp_list;
		// while (env)
		// {
		// 	if (!(ft_strncmp(env->key, "PWD", 3)))
		// 	{
		// 		ft_printf("VALUE: %s\n", env->value);
		// 	}
		// 	env = env->next;
		// }

		ft_start_executing(minip, &mini->cmd_list, &mini->envp_list);

		// t_list *env2 = mini->envp_list;
		// while (env2)
		// {
		// 	if (!(ft_strncmp(env2->key, "PWD", 3)))
		// 	{
		// 		ft_printf("New pwd: %s\n", env2->value);
		// 	}
		// 	env2 = env2->next;
		// }

		while (mini->cmd_list)
		{
			tmp = mini->cmd_list;
			mini->cmd_list = mini->cmd_list->next;
			//free_stuff(tmp, tmp->cmd_m, NULL, NULL);
		}
		//necessario resettare tutti i parametri fra un iterazione e l altra
		ft_printf("exit s: %d\n", g_exit_status);
		mini->flush = 0;
		mini->index = 0;
		mini->built_in_counter = 0;
		mini->cmd_num = 0;
		ft_lst_delete(&mini->cmd_list);
	}
	return ;
}

void	free_env_keyvalue(t_list *envp)
{
	t_list *env;

	env = envp;
	while (env)
	{
		if (env->key != NULL)
		{
			//ft_printf("//freeING %p %s\n", env->key, env->key);
			//free(env->key);
			env->key = NULL;
		}
		if (env->value != NULL)
		{
			//ft_printf("//freeING %p %s\n", env->value, env->value);
			//free(env->value);
			env->value = NULL;
		}
		env = env->next;
	}
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
	g_exit_status = 0;
	
	//free_env_keyvalue(mini->envp_list);
	ft_lst_delete(&mini->envp_list);
	//free(mini);
	//free(miniflags);
	return (0);
}
