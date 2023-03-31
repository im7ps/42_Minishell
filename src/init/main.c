/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:14:12 by dgioia            #+#    #+#             */
/*   Updated: 2023/03/31 18:47:22 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

void	free_env_keyvalue(t_list *envp)
{
	t_list *env;

	env = envp;
	while (env)
	{
		if (env->key != NULL)
		{
			//free(env->key);
			env->key = NULL;
		}
		if (env->value != NULL)
		{
			//free(env->value);
			env->value = NULL;
		}
		env = env->next;
	}
}

int	ft_get_starting_shllv(t_list **envp)
{
	int				n;
	t_list			*env;

	n = 0;
	env = *envp;
	while (env != NULL)
	{
		if (!(ft_strncmp(env->key, "SHLVL", 6)))
		{
			n = ft_atoi(env->value);
		}
		env = env->next;
	}
	return (n);
}

int	ft_update_shellv(t_garbage **garbage, t_list **envp, int flag)
{
	t_list			*env;
	static int		n;

	env = *envp;
	n = ft_get_starting_shllv(envp);
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
			env->value = ftm_itoa(garbage, n);
		}
		env = env->next;
	}
	if (n == 0)
	{
		return (1);
	}
	return (0);
}

char	ft_whatis(char c)
{
	if (ft_isdigit(c))
		return ('d');
	else if (ft_isalpha(c))
		return ('c');
	else if ((c < 48 && c > 32) || (c > 57 && c < 65) || \
		(c > 90 && c < 96) || (c > 122 && c < 127))
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
	//g_exit_status = ft_atoi(tmp);
	free(tmp);
	return (0);
}

int ft_type_router(char c)
{
	if (ft_whatis(c) == 'c')
	{
		//g_exit_status = 255;
		return (1);
	}
	else if (ft_whatis(c) == 'd')
	{
		return (0);
	}
	else if (ft_whatis(c) == 's')
	{
		//g_exit_status = 0;
		return (1);
	}
	return (1);
}

int	ft_is_exit(char *str)
{
	int	i;
	int router;

	if (str[0] != 'e' || str[1] != 'x' || str[2] != 'i' || str[3] != 't')
		return (0);
	i = 4;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			;
		else
		{
			router = ft_type_router(str[i]);
			if (router == 1)
				return (0);
			else if (router == 0)
			{
				if (ft_handle_exit_digit(str + i) == -1)
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	ft_handle_shllv(t_minishell **minip)
{
	t_minishell *mini;

	mini = *minip;
	if (ft_is_exit(mini->input))
	{
		if (ft_update_shellv(&mini->garbage, &mini->envp_list, -1))
		{
			ft_printf("Caricamento procedura d'uscita in corso, non spegnere il computer\n");
			return (0);
		}
	}
	else if (!(ft_strncmp(mini->input, "./minishell", 11)))
	{
		ft_update_shellv(&mini->garbage, &mini->envp_list, 1);
		return (1);
	}
	return (1);
}

void	ft_check_path(t_minishell **minip, t_list **envp)
{
	t_list *env;
	t_minishell *mini;

	mini = *minip;
	env = *envp;
	while (env != NULL)
	{
		if (!(ft_strncmp(env->key, "PATH", 5)))
		{
			mini->nopath = 0;
			return ;	
		}
		env = env->next;
	}
	mini->nopath = 1;
	return ;
}

int ft_input_checklist(t_minishell **minip, t_list **envp)
{
	t_minishell *mini;

	mini = *minip;
	ft_check_path(minip, envp);
	if (!ft_handle_shllv(minip))
	{
		return (1);
	}
	if (ft_input_checker(mini->input, 0, 0, true) != 0)
	{
		ft_printf("Error: è stata scritta qualche cagata astronomica\n");
		return (1);
	}
	return (0);
}

void	ft_execute_mini(t_minishell **minip, char **envp)
{
	t_minishell *mini;

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
		ft_start_executing(&mini, &mini->cmd_list, &mini->envp_list);
		ft_mini_initializer(&mini, envp, 0);
		ft_lst_delete(&mini->cmd_list);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell *mini;

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
