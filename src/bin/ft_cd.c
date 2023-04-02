/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:35:55 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 12:03:09 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_change_oldpwd(t_list **envp, char *oldpwd)
{
	t_list	*env;

	env = *envp;
	while (env)
	{
		if (!ft_strncmp(env->key, "OLDPWD", 6))
		{
			env->value = oldpwd;
			ft_printf("Changing oldpwd value to: %s\n", env->value);
		}
		env = env->next;
	}
}

void	cd_path(t_list **envp)
{
	t_list	*env;

	env = *envp;
	while (env)
	{
		if (!ft_strncmp(env->key, "PWD", 3))
		{
			ft_change_oldpwd(envp, env->value);
			env->value = getcwd(NULL, 0);
			ft_printf("Changing pwd value to: %s\n", env->value);
		}
		env = env->next;
	}
}

int	ft_cd(t_list *head, t_list **envp)
{
	char	*tmp;
	int		len;

	len = ft_count_rows(head->cmd_m);
	if (len == 1)
	{
		tmp = getenv("HOME");
		chdir(tmp);
		cd_path(envp);
		return (0);
	}
	else if (head->cmd_m[1] != NULL && head->cmd_m[1][0] == '~')
	{
		tmp = getenv("HOME");
		chdir(tmp);
		if (chdir(head->cmd_m[1] + 2) == -1)
			return (1);
		cd_path(envp);
	}
	else if (chdir(head->cmd_m[1]) == -1)
		return (1);
	else
		cd_path(envp);
	return (0);
}
