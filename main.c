/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:45:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/01/13 19:07:37 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_stuff(char *input, char **matrix)
{
	int i;

	i = 0;
	if (input)
		free(input);
	if (matrix)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
	rl_clear_history();
}

int	ft_perror(int err)
{
	if(err == QUOTEERR)
		printf("Double quotes not closed properly!\n");
	return (1);
}

int	ft_input_check(char *input)
{
	int i;
	int	dquotes;

	i = 0;
	dquotes = 0;
	while (input[i])
	{
		if (input[i] == '"')
			dquotes++;
		i++;
	}
	if (dquotes % 2 == 1)
		return (ft_perror(QUOTEERR));
	return (0);
}

int	ft_setprompt(t_prompt *prompt, char **envp)
{
	int	i;

	i = 0;
	prompt->name = "minishell> ";	//il nome della shell, viene visualizzato all inizio di ogni nuova riga del terminale
	while (envp[i] && envp)
	{
		i++;
	}
	prompt->envp = (char **) malloc (sizeof(char *) * (i + 1));
	if (!prompt->envp)
		return (ft_perror(MALLOCERR));
	i = 0;
	while (envp[i])
	{
		prompt->envp[i] = ft_strdup(envp[i]);
		if (!prompt->envp[i])
		{
			ft_free_stuff(NULL, prompt->envp);
			return (ft_perror(ENVERR));
		}
		i++;
	}
	prompt->envp[i] = NULL;
	return 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt prompt;
	char	*input;
	char	**args;

	ft_setprompt(&prompt, envp);	//copies the envp content into prompt.envp


    input = readline("Enter the path to the executable: ");
    if (access(input, X_OK) == 0)
	{
		args = malloc(sizeof(char *) * 2);
		args[0] = input;
		args[1] = NULL;
        execve(input, args, NULL);
    }
	else 
	{
		printf("Path non trovato o accesso negato!\n");
        ft_perror(ACCESSERR);
    }

	/*while (argc && argv)
	{
		input = readline(prompt.name);	//legge l input dell utente e salva la stringa
		add_history(input);			//aggiunge l input dell utente alla cronologia (é una funzione di qualche libreria?)
		if (ft_input_check(input))
		{
			break ;
		}
	}*/
	//printf("Percorso: %s\n", getcwd(NULL, 0));
	ft_free_stuff(input, prompt.envp);
	return (0);
}

