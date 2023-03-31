/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 21:41:10 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 21:41:55 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	**ft_whichlist(t_list **export, t_list **env, char *str)
{
	if (ft_strchr(str, '='))
	{
		return (env);
	}
	return (export);
}

int	ft_whereis_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	ft_var_isnew(t_list **head, int j, char *str)
{
	t_list	*node;

	node = *head;
	while (node)
	{
		if (!ft_strncmp(node->key, str, j))
			return (1);
		node = node->next;
	}
	return (0);
}
