/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/10 20:50:50 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_create_list(t_list **cmd_list, char	**full_cmd)
{
	int		i;
    t_list *new_node;
	
	i = 0;
	while (full_cmd[i])
	{
		new_node = ft_malloc_stuff(NODE_NUM);
		new_node->cmd_m = ft_split(full_cmd[i], ' ');
		new_node->cmd = NULL;
		new_node->args = NULL;
		new_node->flags = NULL;
		new_node->key = NULL;
		new_node->value = NULL;
		new_node->next = NULL;
		ft_lstadd_back(cmd_list, new_node);
		i++;
	}
	return ;
}

void	ft_quotes_management(char	c, t_miniflags **minif)
{
	t_miniflags *flags;

	flags = *minif;
	if (c == 34 && !(flags->d_quote || flags->s_quote))
	{
		flags->d_quote = true;
		ft_printf("dquotes activated\n");
	}
	else if (c == 39 && !(flags->d_quote || flags->s_quote))
	{
		flags->s_quote = true;
		ft_printf("squotes activated\n");
	}
	else if (c == 34 && flags->d_quote)
	{
		flags->d_quote = false;
		ft_printf("dquotes disabled\n");
	}
	else if (c == 39 && flags->s_quote)
	{
		flags->s_quote = false;
		ft_printf("squotes disabled\n");
	}
}

// void	ft_attributes_router()
// {

// }

/*
*	analizzo la lista nodo per nodo
*	il comando é sempre la prima stringa che legge il programma
*	a prescindere se inizia come: echo, >> o $VAR, perché 
*	poi avverrá un reindirizzamento
*/
void	ft_attributes_management(t_minishell **minip, t_miniflags **minif)
{
	t_minishell *mini;
	t_miniflags *flags;
	t_list 		*cmd_node;
	int			i;
	int			j;

	mini = *minip;
	flags = *minif;
	cmd_node = mini->cmd_list;
	while (cmd_node)
	{
		if (cmd_node->cmd == NULL)
			cmd_node->cmd = cmd_node->cmd_m[0];
		i = 1;
		//ft_attributes_router(&cmd_node, &flags);
		while (cmd_node->cmd_m[i])
		{
			j = 0;
			while (cmd_node->cmd_m[i][j])
			{
				//attiva e disattiva le quotes
				ft_quotes_management(cmd_node->cmd_m[i][j], &flags);
				if (flags->d_quote)
					ft_printf("double activated\n");
				/*adesso che sappiamo se siamo o no dentro delle quotes si procede ad
				individuare con che comando abbiamo a che fare per dividere meglio
				nome flags e args*/
				j++;
			}
			i++;
		}
		cmd_node = cmd_node->next;
	}
}

int	ft_lexer(t_minishell **minip, t_miniflags **minif)
{
	t_minishell *mini;
	t_miniflags *flags;
	int			cmd_num;
	int			i;

	mini = *minip;
	flags = *minif;
	mini->full_cmd = ft_split_variant(mini->input);
	i = 0;
	while (mini->full_cmd[i])
	{
		ft_printf("%s\n", mini->full_cmd[i]);
		i++;
	}
	//ft_create_list(&mini->cmd_list, mini->full_cmd);
	//ft_attributes_management(&mini, &flags);
	//ft_dollar_expander(&mini);
	//ft_start_executing(&mini->cmd_list);
	return (0);
}
