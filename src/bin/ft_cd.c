/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:35:55 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 14:49:34 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_change_oldpwd(t_garbage **garbage, t_list **envp, char *oldpwd)
{
	t_list	*env;

	(void)garbage;
	env = *envp;
	while (env)
	{
		if (!ft_strncmp(env->key, "OLDPWD", 6))
		{
			ft_strlcpy(env->value, oldpwd, ft_strlen(oldpwd) + 1);
		}
		env = env->next;
	}
	//free(oldpwd);
	//oldpwd = NULL;
}

void	cd_path(t_garbage **garbage, t_list **envp)
{
	t_list	*env;
	char	*tmp;

	env = *envp;
	tmp = getcwd(NULL, 0);
	while (env)
	{
		if (!ft_strncmp(env->key, "PWD", 3))
		{
			ft_change_oldpwd(garbage, envp, env->value);
			ft_strlcpy(env->value, tmp, ft_strlen(tmp) + 1);
		}
		env = env->next;
	}
	free(tmp);
	tmp = NULL;
}

int	ft_cd(t_garbage **garbage, t_list *head, t_list **envp)
{
	char	*tmp;
	int		len;

	len = ft_count_rows(head->cmd_m);
	if (len == 1)
	{
		tmp = getenv("HOME");
		chdir(tmp);
		cd_path(garbage, envp);
		return (0);
	}
	else if (head->cmd_m[1] != NULL && head->cmd_m[1][0] == '~')
	{
		tmp = getenv("HOME");
		chdir(tmp);
		if (chdir(head->cmd_m[1] + 2) == -1)
			return (1);
		cd_path(garbage, envp);
	}
	else if (chdir(head->cmd_m[1]) == -1)
		return (1);
	else
		cd_path(garbage, envp);
	return (0);
}
