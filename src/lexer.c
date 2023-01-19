/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/01/19 11:13:44 by sgerace          ###   ########.fr       */
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
			(input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123)))
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


t_list	*ft_lstnew(void *full_cmd)
{
	t_list	*nodo;

	nodo = (t_list *) malloc (sizeof(t_list));	//crea un nuovo nodo, come grandezza per l area di memoria da allocare usiamo la grandezza della struttura
	if (nodo == NULL)
		return (NULL);
	nodo->cmd_m = ft_split(full_cmd, ' ');
	nodo->next = NULL;
	return (nodo);
}

void	ft_create_list(t_list **cmd_list, char	**full_cmd)
{
	t_list	*tmp;
	int		i;
	
	i = 0;
	tmp = *cmd_list;
	while (full_cmd[i])
	{
		tmp = ft_lstnew(full_cmd[i]);
		ft_lstadd_back(cmd_list, tmp);
		i++;
	}
	return ;
}

int	ft_lexer(t_minishell *mini)
{
	if (ft_check_special_char(mini->input))
		return (ft_perror(ERR_INPUT, NULL));
	if (ft_check_quotes(mini->input))
		return (ft_perror(ERR_QUOTE, NULL));
	mini->full_cmd = ft_split(mini->input, '|');
	ft_create_list(&mini->cmd_list, mini->full_cmd);
	while (mini->cmd_list)
	{
		printf("CMD: %s\n", mini->cmd_list->cmd_m[0]);
		printf("ARG: %s\n", mini->cmd_list->cmd_m[1]);
		mini->cmd_list = mini->cmd_list->next;
	}
	return (0);
}
