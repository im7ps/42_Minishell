/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:19 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 11:21:43 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_write_inpipes(t_list	*env, int **pipes, int index)
{
	if (env->key)
		write(pipes[index + 1][1], env->key, \
			(sizeof(char) * ft_strlen(env->key)));
	if (env->value)
	{
		write(pipes[index + 1][1], "=", sizeof(char));
		write(pipes[index + 1][1], env->value, \
			(sizeof(char) * ft_strlen(env->value)));
	}
	write(pipes[index + 1][1], "\n", sizeof(char));
}

int	ft_env(t_list **envp, int **pipes, int index, t_list *head)
{
	t_list	*env;

	env = *envp;
	while (env)
	{
		if (head->final_red != 0)
			ft_write_inpipes(env, pipes, index);
		else
		{
			if (env->key)
				write(1, env->key, (sizeof(char) * ft_strlen(env->key)));
			if (env->value)
			{
				write(1, "=", sizeof(char));
				write(1, env->value, (sizeof(char) * ft_strlen(env->value)));
			}
			write(1, "\n", sizeof(char));
		}
		env = env->next;
	}
	return (0);
}
