/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:16:59 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/06 18:46:21 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(t_list *head, t_list **envp, int **pipes, int index, int cmd_num)
{
	if (!ft_strncmp(head->cmd_m[0], "echo", 4))
	{
		// ft_printf("FOUND %s\n", head->cmd_m[0]);
		// return (1);
		return (!(ft_echo(head, pipes, index, cmd_num)));
	}
	else if (!ft_strncmp(head->cmd_m[0], "cd", 2))
	{
		return (!(ft_cd()));
	}
	else if (!ft_strncmp(head->cmd_m[0], "pwd", 3))
	{
		return (!(ft_pwd()));
	}
	else if (!ft_strncmp(head->cmd_m[0], "export", 6))
	{
		return (!(ft_export()));
	}
	else if (!ft_strncmp(head->cmd_m[0], "unset", 5))
	{
		return (!(ft_unset()));
	}
	else if (!ft_strncmp(head->cmd_m[0], "env", 3))
	{
		return (!(ft_env()));
	}
	return (0);
}