/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:19 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/26 00:53:00 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		{
			if (env->key)
				write(pipes[index + 1][1], env->key, (sizeof(char) * ft_strlen(env->key)));
			write(pipes[index + 1][1], "=", sizeof(char));
			if (env->value)
				write(pipes[index + 1][1], env->value, (sizeof(char) * ft_strlen(env->value)));
			write(pipes[index + 1][1], "\n", sizeof(char));
		}
		else
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}