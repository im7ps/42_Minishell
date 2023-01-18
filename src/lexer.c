/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/01/18 20:57:57 by sgerace          ###   ########.fr       */
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

/*diocan non funziona*/
t_list	*ft_lstnew(void *content)
{
	t_list	*nodo;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nodo = (t_list *) malloc (sizeof(t_list));	//crea un nuovo nodo, come grandezza per l area di memoria da allocare usiamo la grandezza della struttura
	if (nodo == NULL)
		return (NULL);
	nodo->cmd_m = ft_split(content, ' ');
	while (nodo->cmd_m[j])
	{
		j++;
	}
	nodo->flag = NULL;
	while (nodo->cmd_m[i])
	{
		nodo->cmd_name = nodo->cmd_m[0];
		if (i != 0 && i != j)
			nodo->flag = ft_strjoin(nodo->flag, nodo->cmd_m[i]);
		if (i != 0)
			nodo->arg = nodo->cmd_m[i - 1];
		i++;
	}
	nodo->next = NULL;
	return (nodo);
}

/*diocan non funziona*/
void	ft_create_list(t_minishell *mini)
{
	t_list	*cmd_list;
	int		i;

	i = 0;
	cmd_list = NULL;
	while (mini->full_cmd[i])
	{
		cmd_list = ft_lstnew(mini->full_cmd[i]);
		//ft_lstadd_back(&mini->cmd_list, cmd_list);
		i++;
	}
	printf("%s\n", cmd_list->flag);
}

int	ft_lexer(t_minishell *mini)
{
	if (ft_check_special_char(mini->input))
		return (ft_perror(ERR_INPUT, NULL));
	if (ft_check_quotes(mini->input))
		return (ft_perror(ERR_QUOTE, NULL));
	mini->full_cmd = ft_split(mini->input, '|');
	ft_create_list(mini);
	return (0);
}
