/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:19 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/01 00:05:28 by sgerace          ###   ########.fr       */
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

int	ft_env(t_list **envp, int **pipes, int index, char **cmd_m)
{
	t_list	*env;
	int		i;

	i = 0;
	while (cmd_m[i])
	{
		i++;
	}
	env = *envp;
	while (env)
	{
		if (!ft_strncmp(cmd_m[i - 1], "|", 1))
			ft_write_inpipes(env, pipes, index);
		else
			if (env->key)
				write(1, env->key, (sizeof(char) * ft_strlen(env->key)));
		if (env->value)
		{
			write(1, "=", sizeof(char));
			write(1, env->value, (sizeof(char) * ft_strlen(env->value)));
		}
		write(1, "\n", sizeof(char));
		env = env->next;
	}
	return (0);
}
