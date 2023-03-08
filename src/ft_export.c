/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:24 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/09 00:32:51 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_delete_quotes(char *value)
{
	int		i;
	int		counter;
	char	*newvalue;
	int		k;

	i = 0;
	counter = 0;
	while (value[i])
	{
		if (ft_is_escaped(value[i]) == 0)
		{
			counter++;
		}
		i++;
	}
	if (counter > 0)
	{
		newvalue = (char *) malloc (sizeof(char) * (counter + 1));
		if (!newvalue)
			return (NULL);
		k = 0;
		i = 0;
		while (value[i])
		{
			if (ft_is_escaped(value[i]) == 0)
			{
				newvalue[k] = value[i];
				k++;
			}
			i++;
		}
		newvalue[k] = '\0';
		free(value);
		return (newvalue);
	}
	return (value);	
}

int	ft_export(t_list *head, t_list **envp)
{
	int		i;
	int		j;
	int		k;
	t_list 	*new_node;

	i = 1;
	while (head->cmd_m[i])
	{
		if (!(ft_strncmp(head->cmd_m[i], "|", 1)) || !(ft_strncmp(head->cmd_m[i], ">", 1)) || !(ft_strncmp(head->cmd_m[i], "<", 1)) || !(ft_strncmp(head->cmd_m[i], ">>", 2)) || !(ft_strncmp(head->cmd_m[i], "<<", 2)))
		{
			ft_printf("Ending with redirection\n");
			i++;
		}
		else
		{
			new_node = (t_list *) malloc (sizeof(t_list));
			if (new_node == NULL)
				return (1);

			j = 0;
			while (head->cmd_m[i][j] != '=')
			{
				j++;
			}
			new_node->key = ft_substr_old(head->cmd_m[i], 0, j);
			k = 0;
			while (head->cmd_m[i][j + k] != '\0')
			{
				k++;
			}
			new_node->value = ft_strndup((head->cmd_m[i] + j + 1), k);
			new_node->value = ft_delete_quotes(new_node->value);

			new_node->name = NULL;
			new_node->args = NULL;
			new_node->flags = NULL;
			new_node->end = NULL;
			new_node->next = NULL;
			ft_lstadd_back(envp, new_node);
			i++;
		}
	}
	return (0);
}