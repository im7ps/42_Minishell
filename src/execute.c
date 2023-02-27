/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/27 19:12:51 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_execute_single(int **pipes, char **args, t_list *head, int cmd_num)
{
	// ft_printf("Dasdasdasd\n");
	char *arg1s[] = {"/bin/echo", "SINGLE", NULL};
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
	execve(arg1s[0], arg1s, NULL);
	ft_printf("Problems with execveS\n");
	return 0;
}

int ft_execute_first(int **pipes, char **args, t_list *head, int cmd_num, int index)
{
	int err = 0;
	// ft_printf("FIRST\n");

	close(pipes[index][0]);

	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2F\n");
	}
	close(pipes[index + 1][1]);

	execve(head->cmd_m[0], args, NULL);
	ft_printf("Problems with execveF\n");

	return (1);
}

int	ft_execute_middle(int **pipes, char **args, t_list *head, int cmd_num, int index)
{
	int err = 0;
	// ft_printf("MIDDLE\n");

	err = dup2(pipes[index + 1][1], STDOUT_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2M1\n");
	}
	close(pipes[index + 1][1]);

	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2M2\n");
	}
	close(pipes[index][0]);

	execve(head->cmd_m[0], args, NULL);
	ft_printf("Problems with execveM\n");
	return (1);
}


int	ft_execute_last(int **pipes, char **args, t_list *head, int cmd_num, int index)
{
	int err = 0;
	// ft_printf("LAST\n");
	
	close(pipes[index + 1][1]);
	err = dup2(pipes[index][0], STDIN_FILENO);
	if (err == -1)
	{
		ft_printf("Error using dup2L\n");
	}
	close(pipes[index][0]);

	// ft_printf("L%sL\n", head->cmd_m[0]);
	execve(head->cmd_m[0], args, NULL);
	ft_printf("Problems with execveL\n");
	return (1);
}

int	ft_execute_command(int **pipes, char **args, t_list *head, int cmd_num, int index)
{
	int i;
	
	i = 0;
	while (i < cmd_num + 1)
	{
		if (i != index)
		{
			close(pipes[i][0]);
		}
		if (i != index + 1)
		{
			close(pipes[i][1]);
		}
		i++;
	}

	if (cmd_num == 1)
	{
		ft_execute_single(pipes, args, head, cmd_num);
	}
	else if (index == 0 && cmd_num != 1)
	{
		ft_execute_first(pipes, args, head, cmd_num, index);
	}
	else if (index != cmd_num - 1 && index != 0)
	{
		ft_execute_middle(pipes, args, head, cmd_num, index);
	}
	else if (index == cmd_num - 1)
	{
		ft_execute_last(pipes, args, head, cmd_num, index);
	}
	return (1);
}

char	*ft_trypath(char	*cmd, t_list **envp)
{
	t_list 	*env;
	char	**trypath;
	char	*cmdcopy;
	int		i;

	i = 0;
	env = *envp;
	while (env)
	{
		if (!(ft_strncmp("PATH", env->key, 4)))
		{
			trypath = ft_old_split(env->value, ':');
		}
		i++;
		env = env->next;
	}

	cmdcopy = cmd;

	i = 0;
	while (trypath[i])
	{
		trypath[i] = ft_strjoin(trypath[i], "/");
		cmd = ft_strjoin(trypath[i], cmd);
		if (access(cmd, X_OK) == 0)
		{
			// ft_printf("found!\n");
			return (cmd);
		}
		else
		{
			// ft_printf("Not found!\n");
			cmd = cmdcopy;
		}
		i++;
	}
	return (NULL);
}

char	**ft_load_args(t_list **cmd_list, t_list **envp)
{
	int		i;
	char 	**args;
	t_list	*head;

	i = 0;
	head = *cmd_list;
	while (head->cmd_m[i])
	{
		i++;
	}
	args = (char **) malloc (sizeof(char *) * (i + 1));
	head->cmd_m[0] = ft_trypath(head->cmd_m[0], envp);
	i = 0;
	while (head->cmd_m[i])
	{
		args[i] = (char *) malloc (sizeof(char) * ft_strlen(head->cmd_m[i]) + 1);
		args[i] = head->cmd_m[i];
		i++;
	}
	if (args[i - 1][ft_strlen(head->cmd_m[i - 1]) - 1] == '>' || args[i - 1][ft_strlen(head->cmd_m[i - 1]) - 1] == '<' || args[i - 1][ft_strlen(head->cmd_m[i - 1]) - 1] == '|')
	{
		ft_printf("Sostituito redirection with NULL\n");
		args[i - 1] = NULL;
	}
	return (args);
}

int ft_start_executing(t_list	**cmd_list, int cmd_num, t_list **envp)
{
	t_list		*head;
	int			*pid;
	int			i;
	int 		**pipes;
	char		**args;

	pid = (int*) malloc (sizeof(int) * cmd_num);
	pipes = (int**) malloc (sizeof(int) * cmd_num + 1);
	

	args = NULL;
	head = *cmd_list;

	i = 0;
    while(i < cmd_num + 1) 
	{
		pipes[i] = (int *) malloc (sizeof(int) * 2);
        if (pipe(pipes[i]) == -1) 
		{
            ft_printf("Error with creating pipe\n");
            return 1;
        }
		i++;
    }

	i = 0;
	while(head)
	{
		args = ft_load_args(&head, envp);

		pid[i] = fork();
		if (pid[i] < 0)
			return (2);

		if (pid[i] == 0)
		{
			if (ft_execute_command(pipes, args, head, cmd_num, i) == 1)
				return (1);
			return (0);
		}
		i++;
		head = head->next;
	}
	if (cmd_num != 1)		//le pipes sono già state chiuse in ft_execute_single
	{
		i = 0;
		while (i < cmd_num + 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i++;
		}
	}

	i = 0;
	while (i < cmd_num)
	{
		wait(NULL);
		i++;
	}

	return (0);
}