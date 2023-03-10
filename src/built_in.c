/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:16:59 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/10 17:53:59 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(t_list *head, t_list **envp, int **pipes, int index, int cmd_num)
{
	if (!ft_strncmp(head->cmd_m[0], "echo", 4))
	{
		return (!(ft_echo(head, pipes, index, cmd_num)));
	}
	else if (!ft_strncmp(head->cmd_m[0], "cd", 2))
	{
		return (!(ft_cd(head, envp)));
	}
	else if (!ft_strncmp(head->cmd_m[0], "pwd", 3))
	{
		return (!(ft_pwd()));
	}
	else if (!ft_strncmp(head->cmd_m[0], "export", 6))
	{
		return (!(ft_export(head, envp)));
	}
	else if (!ft_strncmp(head->cmd_m[0], "unset", 5))
	{
		return (!(ft_unset(head, envp, NULL)));
	}
	else if (!ft_strncmp(head->cmd_m[0], "env", 3))
	{
		return (!(ft_env(envp)));
	}
	return (0);
}