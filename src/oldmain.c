/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:45:51 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/15 16:39:37 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	//rl_clear_history();
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
		return (ft_perror(ERR_QUOTE));
	return (0);
}

int	ft_matrixlen(char **matrix)
{
	int	i;
	
	i = 0;
	while (matrix[i] && matrix)
	{
		i++;
	}
	return (i);
}

int	ft_path_case(char *input)
{
	char	**args;
	char	*path;			//una stringa dove verrà copiata l intera variabile PATH
	char	**path_token;	//una matrice con tutti gli absolute PATH in cui il programma cercherà l eseguibile se non è specificato dall utente nè un path assoluto nè uno relativo
	int		path_num;		//numero dei percorsi contenuti in PATH in cui bisogna cercare
	char	executable_path[1024]; //gli do abbastanza spazio per copiarci dentro un path di lunghezza max 1024

	path = getenv("PATH");
	if (!path)
		return (ft_perror(PATHERR));
	path_token = ft_split(path, ':');
	path_num = ft_matrixlen(path_token);
	while (path_num > 0)
	{
		ft_strlcpy(executable_path, path_token[path_num - 1], ft_strlen(path_token[path_num - 1]) + 1); //+1 per il NULL terminator
		if (executable_path[ft_strlen(executable_path) - 1] != '/')				//quasi tutti i path sono separati da ":" ma alcuni path terminano con "/:", perciò va fatto un controllo per evitare di creare path del tipo: usr/bin//:
			ft_strlcat(executable_path, "/", ft_strlen(executable_path) + 2); 	//+1 per il NULL terminator delle stringhe di exec_path e +1 per il nuovo carattere da appendere
		ft_strlcat(executable_path, input, ft_strlen(executable_path) + ft_strlen(input) + 1);
		if (access(executable_path, X_OK) == 0)
		{
			args = malloc(sizeof(char *) * 2);
			args[0] = executable_path;
			args[1] = NULL;
			execve(executable_path, args, NULL);
		}
		path_num--;
	}
	ft_printf("PATH non trovato o accesso negato!\n");	//se riusciamo ad arrivare fuori dal while vuol dire che in nessun percorso di PATH è stata trovata la corrispondenza PATH/input, quindi non è stato trovato l eseguibile
	ft_perror(ACCESSERR);
	return (0);
}

int	ft_abs_rel_path_case(char *input)
{
	char	**args;

	if (access(input, X_OK) == 0)
	{
		args = malloc(sizeof(char *) * 2);
		args[0] = input;
		args[1] = NULL;
        execve(input, args, NULL);
    }
	else 
	{
		ft_printf("Path non trovato o accesso negato!\n");
        ft_perror(ACCESSERR);
    }
	return (0);
}

int ft_manage_executable()
{
	char	*input;

	input = readline("Enter the path to the executable: ");
	if (!input)
		return (ft_perror(READLINEERR));
	//if utente usa la variabile d ambiente PATH
	if (ft_path_case(input))
		return (1);
	//if utente usa un path relativo "./ o ../" o assoluto "/"
	if (ft_abs_rel_path_case(input))
		return (1);
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

int	ft_echo_handler();

// void	ft_find_cmd(char *input)
// {
// 	if (!(ft_strncmp("echo", input, ft_strlen("echo"))))
// 		ft_echo_handler();
// 	else if (!(ft_strncmp("cd", input, ft_strlen("echo"))))
// 		ft_cd_handler();
// 	else if (!(ft_strncmp("pwd", input, ft_strlen("echo"))))
// 		ft_pwd_handler();
// 	else if (!(ft_strncmp("export", input, ft_strlen("echo"))))
// 		ft_export_handler();
// 	else if (!(ft_strncmp("unset", input, ft_strlen("echo"))))
// 		ft_unset_handler();
// 	else if (!(ft_strncmp("env", input, ft_strlen("echo"))))
// 		ft_env_handler();
// 	else if (!(ft_strncmp("exit", input, ft_strlen("echo"))))
// 		ft_exit_handler();
// 	else
// 		ft_printf("Command %s not found.\n", input);
// }

// int	ft_check_input(char *input)
// {
// 	int	i;
// 	int	quotes;

// 	i = 0;
// 	quotes = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '"' || input[i] == '\'')
// 		if (input[i] == '&')
// 	}
// 	return (0);
// }

// int	ft_parser(t_prompt *prompt)
// {
// 	char	*input;
// 	int		i;

// 	while (1)
// 	{
// 		input = readline(prompt->name);
// 		add_history(input);
// 		// if (ft_check_input(input))
// 		// 	return (ft_perror(ERR_INPUT));
// 		builtin(input);
// 	}
// 	//ECHO -N CD (ONLY RELATIVE OR ABSOLUTE) PWD EXPORT UNSET ENV EXIT
// 	//ft_find_cmd(input);
// 	return (0);
// }

void	check_cmd(char *output)
{
	char **cmd;

	cmd = ft_split(output, ' ');
	if(builtin(cmd))
		ft_perror(ERR_NCMD);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*output;

// 	while (argc && argv)
// 	{
// 		output = readline("minishell> ");
// 		add_history(output);	
// 		check_cmd(output);
// 	}
// 	return (0);
// }


// int	main(int argc, char **argv, char **envp)
// {
// 	t_prompt prompt;

// 	ft_setprompt(&prompt, envp);	//copies the envp content into prompt.envp
// 	//ft_manage_executable();
// 	ft_parser(&prompt); //legge l input lo suddivide in comando - opzione - argomento
// 	/*while (argc && argv)
// 	{
// 		input = readline(prompt.name);	//legge l input dell utente e salva la stringa
// 		add_history(input);			//aggiunge l input dell utente alla cronologia (é una funzione di qualche libreria?)
// 		if (ft_input_check(input))
// 		{
// 			break ;
// 		}
// 	}*/
// 	//ft_printf("Percorso: %s\n", getcwd(NULL, 0));
// 	//ft_free_stuff(input, prompt.envp);
// 	return (0);
// }

