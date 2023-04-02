/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/04/02 12:42:40 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_link_prev(int i, t_list *n_node, t_list *p_node, t_list *cmd_list)
{
	if (i == 0)
		n_node->prev = NULL;
	else
	{
		p_node = ft_lstlast(cmd_list);
		n_node->prev = p_node;
	}
}

t_list	*ft_c_list(t_minishell **m, t_list **cmd_list, char **full_cmd, int i)
{
	int		j;
	t_list	*new_node;
	t_list	*prev_node;

	while (full_cmd[i])
	{
		j = 0;
		new_node = gc_alloc(&(*m)->garbage, (sizeof(t_list)), 0);
		ft_initialize_newnode(new_node);
		new_node->cmd_m = ftm_split(&(*m)->garbage, full_cmd[i], ' ');
		while (new_node->cmd_m[j])
		{
			if (new_node->cmd_m[j][ft_strlen(new_node->cmd_m[j]) - 1] == ' ')
				new_node->cmd_m[j][ft_strlen(new_node->cmd_m[j]) - 1] = '\0';
			j++;
		}
		prev_node = NULL;
		ft_link_prev(i, new_node, prev_node, *cmd_list);
		ft_lstadd_back(cmd_list, new_node);
		i++;
	}
	(*m)->cmd_num = ft_count_commands(&(*m)->cmd_list);
	ft_upload_redirection(&(*m)->cmd_list);
	return (*cmd_list);
}

char	ft_define_quote(char *str)
{
	int		i;
	char	c;

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

char	*ft_quotes_eraser(t_minishell *mini, char *str, int i, int j)
{
	char	*tmp;
	char	c;

	tmp = NULL;
	c = ft_define_quote(str);
	if (c != 0)
	{
		tmp = gc_alloc(&mini->garbage, (sizeof(char) * (ft_strlen(str) - 1)), \
			ft_strlen(str) - 1);
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
	t_minishell	*mini;
	t_list		*cmd;
	int			i;

	mini = *minip;
	mini->full_cmd = ft_split_variant(mini, mini->input);
	mini->cmd_list = ft_c_list(minip, &mini->cmd_list, mini->full_cmd, 0);
	cmd = mini->cmd_list;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd_m[i])
		{
			cmd->cmd_m[i] = ft_dollar_expander(&mini->garbage, cmd->cmd_m[i], \
				mini->envp_list);
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
