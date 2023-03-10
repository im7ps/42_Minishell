/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:31:05 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/10 16:41:41 by sgerace          ###   ########.fr       */
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

	execve(head->cmd_m[0], head->cmd_m, NULL);
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

	execve(head->cmd_m[0], head->cmd_m, NULL);
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
	execve(head->cmd_m[0], head->cmd_m, NULL);
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

char	**ft_delete_redirection(char **cmd_m)
{
	int i;

	i = 0;
	while (cmd_m[i])
	{
		i++;
	}
	if (cmd_m[i - 1][ft_strlen(cmd_m[i - 1]) - 1] == '>' || cmd_m[i - 1][ft_strlen(cmd_m[i - 1]) - 1] == '<' || cmd_m[i - 1][ft_strlen(cmd_m[i - 1]) - 1] == '|')
	{
		ft_printf("Sostituito redirection with NULL\n");
		cmd_m[i - 1] = NULL;
	}
	return (cmd_m);	
}

int ft_start_executing(t_list	**cmd_list, int cmd_num, t_list **envp)
{
	t_list		*head;
	int			*pid;
	int			i;
	int 		**pipes;
	int			not_built_in_counter;
	int			builtin_res;
	char		**args;

	pid = (int*) malloc (sizeof(int) * cmd_num);
	pipes = (int**) malloc (sizeof(int*) * (cmd_num + 1));

	args = NULL;
	head = *cmd_list;

	not_built_in_counter = 0;
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
		ft_printf("Debug: %s\n", head->cmd_m[i]);
		builtin_res = is_builtin(head, envp, pipes, i, cmd_num);
		if (builtin_res)
	 	{
			not_built_in_counter++;
			ft_printf("Eseguito comando builtin\n");
		}
		else if (!builtin_res)
		{
			printf("builtin error\n");
			return (1);
		}
		else
		{
			head->cmd_m[0] = ft_trypath(head->cmd_m[0], envp);
			head->cmd_m = ft_delete_redirection(head->cmd_m);
			pid[i] = fork();
			if (pid[i] < 0)
				return (2);

			if (pid[i] == 0)
			{
				if (ft_execute_command(pipes, args, head, cmd_num, i) == 1)
					return (1);
				return (0);
			}
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
	while (i < cmd_num - not_built_in_counter)
	{
		wait(NULL);
		i++;
	}

	i = 0;
    while(i < cmd_num + 1) 
	{
		//free(pipes[i]);
		i++;
    }
	//free(pipes);
	//free(pid);
	return (0);
}