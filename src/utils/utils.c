/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:08 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/01 00:02:30 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_upload_trypath(t_list	*env, t_minishell **minip)
{
	char	**trypath;

	while (env)
	{
		if (!(ft_strncmp("PATH", env->key, 4)))
		{
			trypath = ft_old_split(minip, env->value, ':');
			return (trypath);
		}
		env = env->next;
	}
	return (NULL);
}

char	*ft_trypath(t_minishell **minip, char	*cmd, t_list **envp)
{
	t_list	*env;
	char	**trypath;
	char	*cmdcopy;
	int		i;

	env = *envp;
	trypath = ft_upload_trypath(env, minip);
	cmdcopy = cmd;
	i = 0;
	while (trypath[i])
	{
		trypath[i] = ftm_strjoin(&(*minip)->garbage, trypath[i], "/", 0);
		cmd = ftm_strjoin(&(*minip)->garbage, trypath[i], cmd, 0);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			cmd = cmdcopy;
		i++;
	}
	return (NULL);
}

int	ft_count_commands(t_list **cmd_list)
{
	t_list	*head;
	int		i;

	i = 0;
	head = *cmd_list;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	ft_count_rows(char **cmd_m)
{
	int	i;

	i = 0;
	while (cmd_m[i])
	{
		i++;
	}
	return (i);
}

bool	ft_define_squotes(char c)
{
	int		qtoggle;
	bool	res;

	res = false;
	ft_is_escaped('r', 1);
	qtoggle = ft_is_escaped(c, 0);
	if (qtoggle == 2)
		res = true;
	else if (qtoggle == -2)
		res = false;
	return (res);
}
