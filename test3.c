/*
*	confronta str con la lista di variabili d'ambiente storata in minip.envp, se c'é
*	corrispondenza allora ritorna la value della key trovata, in caso contrario ritorna NULL
*/
char    *ft_expander_finder(char *str, t_minishell **minip, int i, char *input)
{
	size_t      smaller;
	t_list      *mini;
	char		*tmp;

	tmp = (char *) malloc (sizeof(char) * i);
	ft_strlcpy(tmp, input, i);
	mini = (*minip)->envp_list;
	while (mini)
	{
		smaller = ft_smaller_string(str, mini->key);
		if (ft_strlen(str) == ft_strlen(mini->key))
		{
			if (!(ft_strncmp(str, mini->key, smaller)))
			{
				return (mini->value);
			}
		}
		mini = mini->next;
	}
	return (NULL);
}

/*
*	ft_expander_helper:
*	scorri la stringa trovata dopo il $, alloca una stringa temporanea e avvia ft_expander_helper
*	se la stringa ritornata é diversa da NULL ritorna il valore aggiornato di tmp
*/
char    *ft_expander_helper(t_minishell **minip, char *input)
{
	t_minishell *mini;
	int     	i;
	char    	*tmp;

	mini = *minip;
	i = 0;
	while (((input[i] > 64 && input[i] < 91) || input[i] == 95) && input[i] != '\0')
	{
		i++;
	}
	tmp = ft_expander_finder(tmp, &mini, i + 1, input);
	if (tmp == NULL)
		return (NULL);
	//printf("EXPANDED: %s\n", tmp);
	return (tmp);
}

/*
*	ft_dollar_starter:
*	scansiona la stringa, quando trovi il dollaro assicurati che il carattere seguente
*	sia in maiuscolo o sia un underscore, in caso affermativo avvia ft_expander_helper
*	se il valore ritornato é non NULL aggiorna la stringa da ritornare, in caso
*	contrario ritorna NULL
*/
char	*ft_dollar_starter(t_minishell **minip, char  *str)
{
	t_minishell *mini;
	int			i;
	int 		len;

	mini = *minip;
	i = -1;
	len = ft_strlen(str);
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (i + 1 < len)
			{
				i++;
				if ((str[i] > 64 && str[i] < 91) || str[i] == 95)
				{
					str = ft_expander_helper(&mini, str + i);
					if (str == NULL)
						return (NULL);	
				}
				else if (str[i] == '?')
				{
					//$? va espanso con l exit status dell ultimo processo eseguito (l exit status sará la variabile globale da aggiornare sempre)
					return (NULL);
				}
			}
		}
	}
	return (str);
}

/*  
*   ft_dollar_expander: 
*	scansiona ogni elemento della matrice di comandi, se in un elemento é presente il dollaro
*	avvia dollar_starter, se la funziona ritorna un valore non NULL aggiorna il valore
*	della stringa
*/
char	*ft_dollar_expander(t_minishell **minip)
{
	t_minishell	*mini;
	t_list 		*cmd_list;
	int			i;
	int			j;
	char		*tmp;
	int			quotes;
	int			toggle;

	toggle = 1;
	cmd_list = (*minip)->cmd_list;
	mini = *minip;
	while (cmd_list)
	{
		i = 0;
		while (cmd_list->cmd_m[i])
		{
			j = 0;
			while (cmd_list->cmd_m[i][j])
			{
				quotes = ft_is_escaped(cmd_list->cmd_m[i][j]);
				if (quotes == 2 || quotes == -2) // || quotes == -3
				{
					toggle = toggle * -1;
				}
				if (cmd_list->cmd_m[i][j] == '$' && toggle != -1)
				{
					/*if there is a dollar and the dollar is not inside double or single quotes substitute the variable*/
					tmp = ft_dollar_starter(&mini, cmd_list->cmd_m[i]);
					if (tmp != NULL)
					{
						cmd_list->cmd_m[i] = tmp;
						free(tmp);
					}
				}
				j++;
			}
			i++;
		}
		cmd_list = cmd_list->next;
	}
	return (NULL);
}

int main ()
{
	char *input = "echo testone $PWD | cat -e siuum";

	input = ft_dollar_expander();
}