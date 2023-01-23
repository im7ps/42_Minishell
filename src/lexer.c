/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:44:36 by sgerace           #+#    #+#             */
/*   Updated: 2023/01/23 19:15:14 by sgerace          ###   ########.fr       */
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

// void	ft_check_redirection(t_list **cmd_node, char *cmd)
// {
// 	int		i;
// 	t_list 	*node;

// 	i = 0;
// 	node = *cmd_node;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\'')
// 			node->s_quote++;
// 		if (cmd[i] == '"')
// 			node->d_quote++;
// 		if (i + 2 < ft_strlen(cmd))
// 		{
// 			if (cmd[i] == '>' && !(node->s_quote % 2) && !(node->d_quote % 2))
// 			{	
// 				if (cmd[i + 1] == '>' && cmd[i + 2] == ' ')
// 					node->append_o++;
// 			}
// 			else
// 				node->red_o++;
// 			else if (cmd[i] == '<' && !(node->s_quote % 2) && !(node->d_quote % 2))
// 			{
// 					if (cmd[i + 1] == '<' && cmd[i + 2] == ' ')
// 						node->read_i++;
// 			}
// 				else
// 					node->red_i++;
// 		}
// 		i++;
// 	}
// }

void	ft_create_list(t_list **cmd_list, char	**full_cmd)
{
	int		i;
    t_list *new_node;
	
	i = 0;
	while (full_cmd[i])
	{
		new_node = ft_malloc_stuff(NODE_NUM);
		new_node->cmd_m = ft_split(full_cmd[i], ' ');
		new_node->next = NULL;
		ft_lstadd_back(cmd_list, new_node);
		i++;
	}
	return ;
}

int	ft_start_executing(t_list	**cmd_list)
{
	t_list	*head;

	head = *cmd_list;	
	//fd[0] = read from the pipe, fd[1] = write into the pipe
	int fd[2];
	int	pid1;
	int	pid2;
	// char *args[] = {"echo", "-n", "test\n", NULL};

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		//we are in the child process
		execve("/bin/echo", &head->cmd_m[0], NULL);
		//tutto quello che viene dopo execve viene eseguito solo dal parent
	}
	//andiamo al prossimo nodo della lista
	head = head->next;
	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/bin/echo", &head->cmd_m[0], NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	ft_lexer(t_minishell *mini)
{
	int	cmd_num;

	if (ft_check_special_char(mini->input))
		return (ft_perror(ERR_INPUT, NULL));
	if (ft_check_quotes(mini->input))
		return (ft_perror(ERR_QUOTE, NULL));
	mini->full_cmd = ft_split(mini->input, '|');
	ft_create_list(&mini->cmd_list, mini->full_cmd);
	ft_start_executing(&mini->cmd_list);
	// int		j;
	// while (mini->cmd_list)
	// {
	// 	j = 0;
	// 	while ((mini->cmd_list)->cmd_m[j])
	// 	{
	// 		printf("%s\n", (mini->cmd_list)->cmd_m[j]);
	// 		j++;
	// 	}
	// 	(mini->cmd_list) = (mini->cmd_list)->next;
	// }
	// int i = 0;
	// while (mini->cmd_list)
	// {
	// 	i++;
	// 	if (mini->cmd_list->red_o > 0)
	// 		printf("Nodo %d redirect output at index: %d\n", i, mini->cmd_list->red_o);
	// 	if (mini->cmd_list->red_i > 0)
	// 		printf("Nodo %d redirect input at index: %d\n", i, mini->cmd_list->red_i);
	// 	if (mini->cmd_list->append_o > 0)
	// 		printf("Nodo %d append output at index: %d\n", i, mini->cmd_list->append_o);
	// 	if (mini->cmd_list->read_i > 0)
	// 		printf("Nodo %d read input at index: %d\n", i, mini->cmd_list->read_i);
	// 	mini->cmd_list = mini->cmd_list->next;
	// }
	return (0);
}
