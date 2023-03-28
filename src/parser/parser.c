/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/28 18:10:39 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_initialize_newnode(t_list *new_node)
{
	new_node->name = NULL;
	new_node->args = NULL;
	new_node->flags = NULL;
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->next = NULL;
}

// t_list *ft_create_list(t_minishell **minip, t_list **cmd_list, char	**full_cmd)
// {
// 	int		i;
// 	int		j;
//     t_list *new_node;
	
// 	i = 0;
// 	while (full_cmd[i])
// 	{
// 		j = 0;
// 		new_node = (t_list *) malloc (sizeof(t_list));
// 		new_node->cmd_m = ftm_split(&(*minip)->garbage, full_cmd[i], ' ');
// 		while (new_node->cmd_m[j])
// 		{
// 			if (new_node->cmd_m[j][ft_strlen(new_node->cmd_m[j]) - 1] == ' ')
// 				new_node->cmd_m[j][ft_strlen(new_node->cmd_m[j]) - 1] = '\0';	//l ultimo char é uno spazio, sicuramente dovuto allo split
// 			j++;
// 		}
// 		ft_initialize_newnode(new_node);
// 		ft_lstadd_back(cmd_list, new_node);
// 		i++;
// 	}
// 	(*minip)->cmd_num = ft_count_commands(&(*minip)->cmd_list);
// 	ft_upload_redirection(&(*minip)->cmd_list);
// 	return (*cmd_list);
// }

t_list *ft_create_list(t_minishell **minip, t_list **cmd_list, char	**full_cmd)
{
	int		i;
	int		j;
    t_list *new_node;
	t_list *prev_node; // nuovo puntatore al nodo precedente
	
	i = 0;
	while (full_cmd[i])
	{
		j = 0;
		new_node = (t_list *) malloc (sizeof(t_list));
		ft_initialize_newnode(new_node);
		new_node->cmd_m = ftm_split(&(*minip)->garbage, full_cmd[i], ' ');
		while (new_node->cmd_m[j])
		{
			if (new_node->cmd_m[j][ft_strlen(new_node->cmd_m[j]) - 1] == ' ')
				new_node->cmd_m[j][ft_strlen(new_node->cmd_m[j]) - 1] = '\0';	//l ultimo char é uno spazio, sicuramente dovuto allo split
			j++;
		}
		if (i == 0) {
			new_node->prev = NULL; // il primo nodo non ha un nodo precedente
		} 
		else 
		{
			prev_node = ft_lstlast(*cmd_list); // il nodo precedente è l'ultimo nodo della lista
			new_node->prev = prev_node;
		}
		
		ft_lstadd_back(cmd_list, new_node);
		i++;
	}
	(*minip)->cmd_num = ft_count_commands(&(*minip)->cmd_list);
	ft_upload_redirection(&(*minip)->cmd_list);
	return (*cmd_list);
}


char	ft_define_quote(char *str)
{
	int	i;
	char c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
		}
		i++;
	}
	return (c);
}

char *ft_quotes_eraser(t_minishell *mini, char *str, int i, int j)
{
	char *tmp;
	char c;

	tmp = NULL;
	c = ft_define_quote(str);
	if (c != 0)
	{
		tmp = gc_alloc(&mini->garbage, (sizeof(char) * (ft_strlen(str) - 1)), ft_strlen(str) - 1);
		while (str[i])
		{
			if (str[i] != c)
			{
				tmp[j] = str[i];
				j++;
			}
			i++;
		}
		tmp[j] = '\0';
	}
	if (tmp != NULL)
		return (tmp);
	return (str);
}

int	ft_parser(t_minishell **minip)
{
	t_minishell *mini;
	t_list		*cmd;
	int			i;

	mini = *minip;
	mini->full_cmd = ft_split_variant(mini, mini->input);
	mini->cmd_list = ft_create_list(minip, &mini->cmd_list, mini->full_cmd);
	cmd = mini->cmd_list;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd_m[i])
		{
			cmd->cmd_m[i] = ft_dollar_expander(&mini->garbage, cmd->cmd_m[i], mini->envp_list);
			if (cmd->cmd_m[i] == NULL)
				return (1);
			cmd->cmd_m[i] = ft_quotes_eraser(mini, cmd->cmd_m[i], 0, 0);
			if (cmd->cmd_m[i] == NULL)
				return (1);
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}
