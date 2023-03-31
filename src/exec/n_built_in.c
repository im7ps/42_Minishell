/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_built_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:52:04 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/01 00:06:01 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_non_builtin(t_minishell *m, t_list *head, t_list **envp, int **pip)
{
	pid_t	pid;

	if (head->cmd_m[0][0] != '/')
	{
		head->cmd_m[0] = ft_trypath(&m, head->cmd_m[0], envp);
	}
	if (head->cmd_m[0] == NULL)
	{
		ft_printf("Command not found\n");
		return (1);
	}
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		if (ft_execute_command(m, pip, head))
			return (1);
		return (0);
	}
	return (0);
}
