/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:45:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/01/12 20:43:41 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_stuff(char *input)
{
	if (input)
		free(input);
	rl_clear_history();
}

//caratteri da gestire:
// "", (), []
typedef struct s_input
{
	int tonde;
	int quadre;
	int dquotes;
}	t_input;

void	ft_perror(int err)
{
	if(err == QUOTE)
		printf("Double quotes not closed properly!\n");

}

int	ft_input_check(char *input)
{
	int i;
	t_input check;

	i = 0;
	check.dquotes = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			check.dquotes++;
		}
		i++;
	}
	if (check.dquotes % 2 == 1)
		ft_perror(QUOTE);
	/*
	printf("input: %s\n", input);
	if (input[0] == 'm' && input[1] == 'i')
	{
		printf("satoria\n");
	}
	input[0] = 's';
	printf("input2: %s\n", input);*/
	return (0);
}

int	main(int argc, char **argv)
{
	const char	*prompt;
	char	*input;

	(void)argv;
	prompt = "minishell> ";		//il nome della shell, viene visualizzato all inizio di ogni nuova riga del terminale
	
	while (argc && argv)
	{
		input = readline(prompt);	//legge l input dell utente e salva la stringa
		add_history(input);			//aggiunge l input dell utente alla cronologia (é una funzione di qualche libreria?)
		if (ft_input_check(input))
		{
			
			break;
		}
	}
	//printf("Percorso: %s\n", getcwd(NULL, 0));
	ft_free_stuff(input);		//libera la memoria
	return (0);
}

