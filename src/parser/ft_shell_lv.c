/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_lv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:40:25 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 14:47:15 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_handle_exit_digit(char *str)
{
	size_t	i;
	int		counter;
	char	*tmp;

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
	free(tmp);
	tmp = NULL;
	return (0);
}

int	ft_type_router(char c)
{
	if (ft_whatis(c) == 'c')
	{
		ft_printf("Error numeric argument required\n");
		return (1);
	}
	else if (ft_whatis(c) == 'd')
	{
		return (0);
	}
	else if (ft_whatis(c) == 's')
	{
		ft_printf("Error numeric argument required\n");
		return (1);
	}
	return (1);
}

int	ft_is_exit(char *str)
{
	int	i;
	int	router;

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
		return (1);
	return (0);
}

int	ft_handle_shllv(t_minishell **minip)
{
	t_minishell	*mini;

	mini = *minip;
	if (ft_is_exit(mini->input))
	{
		if (ft_update_shellv(&mini->garbage, &mini->envp_list, -1))
		{
			free((*minip)->input);
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
