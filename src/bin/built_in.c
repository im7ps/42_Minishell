/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:16:59 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 20:19:19 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_exit_status;

int	handle_builtin(t_minishell *mini, t_list *head, t_list **envp, int **pipes, int index)
{
	if (!ft_strncmp(head->cmd_m[0], "echo", 4))
		return (!(ft_echo(head, pipes, index)));
	else if (!ft_strncmp(head->cmd_m[0], "cd", 2))
		return (!ft_cd(head, envp));
	else if (!ft_strncmp(head->cmd_m[0], "pwd", 3))
		return (!(ft_pwd(head, head->cmd_m, pipes, index)));
	else if (!ft_strncmp(head->cmd_m[0], "export", 6))
		return (!(ft_export(mini, head)));
	else if (!ft_strncmp(head->cmd_m[0], "unset", 5))
		return (!(ft_unset(head, envp, NULL, &mini->export_list)));
	else if (!ft_strncmp(head->cmd_m[0], "env", 3))
		return (!(ft_env(envp, pipes, index, head->cmd_m)));
	return (0);
}
