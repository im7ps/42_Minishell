/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/01/19 12:42:24 by sgerace          ###   ########.fr       */
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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp_l;

	if (*lst == NULL)			//se la lista punta a NULL e' una lista vuota, facciamola puntare a new e l'avremo aggiunto "in fondo"
		*lst = new;
	else
	{
		tmp_l = ft_lstlast(*lst);		//tmp_l punta all ultimo elemento non nullo
		tmp_l->next = new;				//settiamo new come il nuovo ultimo nodo modificando il nodo puntato da tmp_l
	}
}

void add_node(t_list **head, char *data) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    new_node->cmd_m = ft_split(data, ' ');
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        t_list *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void	ft_create_list(t_list **cmd_list, char	**full_cmd)
{
	int		i;
	
	i = 0;
	while (full_cmd[i])
	{
		add_node(cmd_list, full_cmd[i]);
		// tmp = ft_lstnew(full_cmd[i]);
		// printf("Sto aggiungendo: %s\n", tmp->cmd_m[0]);
		// ft_lstadd_back(cmd_list, tmp);
		// printf("Ho aggiunto: %s\n", tmp->cmd_m[0]);
		i++;
	}
	printf("Cicli: %d\n", i);
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
	return (0); //uno prova | de provo | tre provoli | quatt provolons
}
