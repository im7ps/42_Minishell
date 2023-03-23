/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/03/23 22:35:28 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status;

int	ft_update_shellv(t_list **envp, int flag)
{
	t_list	*env;
	int		n;

	env = *envp;
	n = 0;
	while (env != NULL)
	{
		if (!(ft_strncmp(env->key, "SHLVL", 6)))
		{
			if (flag > 0)
			{
				n = ft_atoi(env->value) + 1;
			}
			else if (flag < 0)
			{
				n = ft_atoi(env->value) - 1;
			}
			env->value = ft_itoa(n);
			return (ft_atoi(env->value));
		}
		env = env->next;
	}
	return (0);
}

char	ft_whatis(char c)
{
	if (ft_isdigit(c))
		return ('d');
	else if (ft_isalpha(c))
		return ('c');
	else if ((c < 48 && c > 32) || (c > 57 && c < 65) || (c > 90 && c < 96) || (c > 122 && c < 127))
		return ('s');
	return (0);
}

int	ft_handle_exit_digit(char *str)
{
	size_t	i;
	int		counter;
	char *	tmp;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			counter++;
		}
		i++;
	}
	if (i > 3)
		return (-1);
	tmp = (char *) malloc (sizeof(char) * (i + 1));
	tmp[i] = '\0';
	ft_strlcpy(tmp, str, i + 1);
	if (ft_atoi(tmp) > 255)
		return (-1);
	g_exit_status = ft_atoi(tmp);
	return (0);
}

int ft_type_router(char c)
{
	if (ft_whatis(c) == 'c')
	{
		g_exit_status = 255;
		return (-1);
	}
	else if (ft_whatis(c) == 'd')
	{
		return (0);
	}
	else if (ft_whatis(c) == 's')
	{
		g_exit_status = 0;
		return (-1);
	}
	return (1);
}

int	ft_is_exit(char *str)
{
	int	i;
	int router;

	if (str[0] != 'e' || str[1] != 'x' || str[2] != 'i' || str[3] != 't')
		return (-1);
	i = 4;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			;
		else
		{
			router = ft_type_router(str[i]);
			if (router == -1)
				return (-1);
			else if (router == 0)
			{
				if (ft_handle_exit_digit(str + i) == -1)
					return (-1);
			}
		}
		i++;
	}
	return (0);
}

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
		if (mini->input == NULL)
		{
			ft_printf("Error: l'input non può essere nullo\n");
			ft_lst_delete(&mini->envp_list);
			//ft_lst_delete(&mini->cmd_list);
			//free(mini);
			//free(flags);
			ft_CTRL_D_handler(0);
		}
		else if (ft_is_exit(mini->input) != -1)
		{
			if (ft_update_shellv(&mini->envp_list, -1) == 0)
			{
				ft_printf("Caricamento procedura d'uscita in corso, non spegnere il computer\n");
				ft_lst_delete(&mini->envp_list);
				//free(mini);
				//free(flags);
				break ;
			}
		}
		else if (!(ft_strncmp(mini->input, "./minishell", 11)))
		{
			ft_update_shellv(&mini->envp_list, 1);
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
			return ;
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
		ft_printf("exit status pre: %d\n", g_exit_status);
		g_exit_status = ft_start_executing(minip, &mini->cmd_list, &mini->envp_list);
		ft_printf("exit status final: %d\n", g_exit_status);

		// t_list *env2 = mini->envp_list;
		// while (env2)
		// {
		// 	if (!(ft_strncmp(env2->key, "PWD", 3)))
		// 	{
		// 		ft_printf("New pwd: %s\n", env2->value);
		// 	}
		// 	env2 = env2->next;
		// }

		// while (mini->cmd_list)
		// {
		// 	tmp = mini->cmd_list;
		// 	mini->cmd_list = mini->cmd_list->next;
			//free_stuff(tmp, tmp->cmd_m, NULL, NULL);
		// }
		//necessario resettare tutti i parametri fra un iterazione e l altra
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
	g_exit_status = 0;

	mini = ft_mini_constructor(&mini, &miniflags, envp);
	ft_execute_mini(&mini, &miniflags);
	
	//free_env_keyvalue(mini->envp_list);
	ft_lst_delete(&mini->envp_list);
	//free(mini);
	//free(miniflags);
	return (0);
}
