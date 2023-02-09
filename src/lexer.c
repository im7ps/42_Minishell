/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/09 17:41:02 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*controlla che ci siano solo caratteri autorizzati: ", ', >, <, $,  , |, -, numeri, lettere*/
int	ft_check_special_char(char	*input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!(input[i] == '"' || input[i] == '$' || input[i] == '\'' || input[i] == '|' || input[i] == '-' || \
			input[i] == '>' || input[i] == '<' || input[i] == ' ' || (input[i] > 47 && input[i] < 58) || \
			input[i] == '_' || (input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123)))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

/*controlla che non ci siano " o ' non utilizzate correttamente*/
int	ft_check_quotes(char	*input)
{
	int	i;
	int	quotes_s;
	int	quotes_d;

	i = 0;
	quotes_s = 0;
	quotes_d = 0;
	while (input[i])
	{
		if (input[i] == '"')
			quotes_d++;
		else if (input[i] == '\'')
			quotes_s++;
		i++;
	}
	if (quotes_d % 2 == 1 || quotes_s % 2 == 1)
		return (1);
	return (0);
}

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
	if (ft_check_special_char(mini->input))
		return (ft_perror(ERR_INPUT, NULL));
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
