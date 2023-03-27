/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:56:56 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/27 17:43:38 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_is_redirection(char *str)
{
	if (!(ft_strncmp(str, "|", 1)))
		return (1);
	else if (!(ft_strncmp(str, ">>", 2)))
		return (2);
	else if (!(ft_strncmp(str, "<<", 2)))
		return (3);
	else if (!(ft_strncmp(str, ">", 1)))
		return (4);
	else if (!(ft_strncmp(str, "<", 1)))
		return (5);
	return (0);
}

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
		// ft_printf("Sostituito redirection with NULL\n");
		cmd_m[i - 1] = NULL;
	}
	return (cmd_m);	
}

void	ft_upload_redirection(t_list **cmd_list)
{
	t_list	*head;
	int		i;

	i = 0;
	head = *cmd_list;
	while(head)
	{
		if (i == 0)
		{
			head->start_red = 0;
		}
		head->final_red = ft_redirection_type(head->cmd_m);
		if (head->next != NULL)
		{
			head->next->start_red = head->final_red;
		}
		i++;
		//ft_printf("Start: %d\n", head->start_red);
		//ft_printf("End: %d\n", head->final_red);
		head->cmd_m = ft_delete_redirection(head->cmd_m);
		head = head->next;
	}
	return ;
}