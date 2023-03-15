/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:56:56 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/15 17:57:23 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_redirection_type(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		i++;
	}
	if (!(ft_strncmp(command[i - 1], "|", 1)))
		return (1);
	else if (!(ft_strncmp(command[i - 1], ">>", 2)))
		return (2);
	else if (!(ft_strncmp(command[i - 1], "<<", 2)))
		return (3);
	else if (!(ft_strncmp(command[i - 1], ">", 1)))
		return (4);
	else if (!(ft_strncmp(command[i - 1], "<", 1)))
		return (5);
	return (0);
}

char	**ft_delete_redirection(char **cmd_m)
{
	int i;

	i = 0;
	while (cmd_m[i])
	{
		i++;
	}
	if (cmd_m[i - 1][ft_strlen(cmd_m[i - 1]) - 1] == '>' || cmd_m[i - 1][ft_strlen(cmd_m[i - 1]) - 1] == '<' || cmd_m[i - 1][ft_strlen(cmd_m[i - 1]) - 1] == '|')
	{
		ft_printf("Sostituito redirection with NULL\n");
		cmd_m[i - 1] = NULL;
	}
	return (cmd_m);	
}
