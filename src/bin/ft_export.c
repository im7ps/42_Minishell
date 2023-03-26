/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:36:24 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/26 13:18:29 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_export_alone(t_list **head, char **str)
{
	t_list *exp;

	exp = *head;
	if ((ft_strlen(str[0]) == 6 && ft_count_rows(str) == 1) && !(ft_strncmp(str[0], "export", 6)))
	{
		while (exp)
		{
			if (exp->value != NULL)
				ft_printf("declare -x %s=\"%s\"\n", exp->key, exp->value);
			else
				ft_printf("declare -x %s\n", exp->key);
			exp = exp->next;
		}
		return (1);
	}
	return (0);
}

int	ft_whereis_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break;
		i++;
	}
	return (i);
}

int	ft_var_isnew(t_list **head, int j, char *str)
{
	t_list *node;

	node = *head;
	while (node)
	{
		if (!ft_strncmp(node->key, str, j))
			return (1);
		node = node->next;
	}
	return (0);
}

void ft_addnode(t_minishell *mini, t_list **head, char *str, int j)
{
	t_list *newnode;

	newnode = NULL;
	newnode = gc_alloc(&mini->garbage, sizeof(t_list), 0);
	newnode->key = gc_alloc(&mini->garbage, (sizeof(char) * ft_strlen(str)), 0);
	ft_strlcpy(newnode->key, str, j + 1);
	if (ft_strchr(str, '='))
	{
		newnode->value = gc_alloc(&mini->garbage, (sizeof(char) * ft_strlen(str)), 0);
		ft_strlcpy(newnode->value, str + j + 1, ft_strlen(str) - j + 1);	
	}
	ft_envp_initialize(newnode);
	ft_lstadd_back(head, newnode);
}

void ft_delete_replace(t_minishell *mini, t_list **head, char *str, int j)
{
	t_list 	*node;
	char	*tmp;

	node = *head;
	tmp = gc_alloc(&mini->garbage, (sizeof(char) * ft_strlen(str)), 1);
	while (node)
	{
		if (!ft_strncmp(node->key, str, j))
		{
			ft_strlcpy(tmp, str, j + 1);
			ft_unset(NULL, head, tmp);
		}
		node = node->next;
	}
	ft_addnode(mini, head, str, j);
}

t_list **ft_whichlist(t_list ** export, t_list ** env, char *str)
{
	if (ft_strchr(str, '='))
	{
		return (env);
	}
	return (export);
}

int	ft_export(t_minishell *mini, t_list *head, t_list **envp, int **pipes, int index)
{
	int		i;
	int		j;
	t_list **heade;

	if (ft_export_alone(&mini->export_list, head->cmd_m))
		return (0);
	i = 1;
	while (head->cmd_m[i])
	{
		heade = ft_whichlist(&mini->export_list, &mini->envp_list, head->cmd_m[i]);
		if ((!(ft_isalpha(head->cmd_m[i][0]))) || head->cmd_m[i][0] == '_')
			return (1);
		j = ft_whereis_equal(head->cmd_m[i]);
		if (!ft_var_isnew(heade, j, head->cmd_m[i]))
		{
			ft_addnode(mini, heade, head->cmd_m[i], j);
		}
		else
		{
			ft_delete_replace(mini, heade, head->cmd_m[i], j);
		}
		i++;
	}
	return (0);
}
