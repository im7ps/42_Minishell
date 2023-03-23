/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:35:55 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/23 01:11:57 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char *malloc_pwd()
// {
//     char *cwd;
//     size_t size;
	
// 	size = 16;
//     while (1) 
// 	{
//         cwd = (char *) malloc (size);
//         if (getcwd(cwd, size) != NULL) 
// 		{
//             return cwd;
//         }
//         if (size >= 1024) 
// 		{
//             printf("Il percorso ha superato 1024 caratteri di lunghezza\n");
//             free(cwd);
//             return NULL;
//         }
//         size *= 2;
//         free(cwd);
//     }
// }

// int	update_env_pwd(char *new_path, t_list **envp)
// {
// 	t_list	*env;

// 	env = *envp;
// 	while (env)
// 	{
// 		if (!(ft_strncmp(env->key, "PWD", 3)))
// 		{
// 			free(env->value);
// 			env->value = NULL;
// 			env->value = new_path;
// 		}
// 		env = env->next;
// 	}
// 	return (0);
// }

// int	ft_absolute_path(char *abs_path, t_list **envp)
// {
//     DIR *dir;

// 	dir = opendir(abs_path);  // apre la directory
//     if (dir) 
// 	{
//         // la directory esiste ed è stata aperta con successo
//         if (chdir(abs_path) == 0) // cambia la directory corrente
// 		{
// 			update_env_pwd(abs_path, envp);
// 		}
// 		else
// 		{
// 			ft_printf("Error changing directory\n");
// 			return (1);
// 		}
// 		closedir(dir);
// 	}
// 	else
// 	{
// 		ft_printf("Il percorso non esiste!\n");
// 		return (1);
// 	}
// 	return (0);
// }

// int	ft_move_forward(char *path, t_list **envp)
// {
// 	char	*abs_path;
// 	char	*pwd_slash;
// 	char	*pwd;

// 	if (path == NULL)
// 		return (1);
// 	pwd = malloc_pwd();
// 	getcwd(pwd, sizeof(pwd));
// 	pwd_slash = ft_strjoin(pwd, "/", 0);
// 	abs_path = ft_strjoin(pwd_slash, path, 0);
// 	if (ft_absolute_path(abs_path, envp))
// 		return (1);
// 	//free(abs_path);
// 	//free(pwd_slash);
// 	return (0);
// }

// int	ft_move_backwards_one(t_list **envp)
// {
// 	int		i;
// 	int		last_slash;
// 	int		res;
// 	char	*newpath;
// 	char	*pwd;

// 	i = 0;
// 	last_slash = 0;
// 	pwd = malloc_pwd();
// 	getcwd(pwd, sizeof(pwd));
// 	while (pwd[i])
// 	{
// 		if (pwd[i] == '/')
// 		{
// 			last_slash = i;
// 		}
// 		i++;
// 	}
// 	newpath = (char *) malloc (sizeof(char) * (last_slash + 1));
// 	ft_strlcpy(newpath, pwd, last_slash + 1);
// 	res = chdir(newpath);
// 	if (res != 0)
// 		return (1);
// 	update_env_pwd(newpath, envp);
// 	return (0);
// }

// int	ft_move_backwards(char *path, t_list **envp)
// {
// 	int		i;
// 	int		counter;
// 	char	*pwd;

// 	i = 0;
// 	counter = 0;
// 	pwd = malloc_pwd();
// 	getcwd(pwd, sizeof(pwd));
// 	while (!(ft_strncmp(path, "../", 3)))
// 	{
// 		path = path + 3;
// 		counter++;
// 	}
// 	while (counter--)
// 	{
// 		ft_move_backwards_one(envp);
// 	}
// 	if (ft_move_forward(path, envp))
// 	{
// 		update_env_pwd(pwd, envp);
// 	}
// 	return (0);
// }

// int	ft_relative_path(char *rel_path, int len, t_list **envp)
// {
// 	int	i;

// 	i = 0;
// 	if ((len == 2 && (rel_path[0] == '.' && rel_path[1] == '/')) || (len == 1 && rel_path[0] == '.'))		//stai nella directory corrente
// 	{
// 		// ft_printf("Input: ./ or .\n");
// 		return (0);
// 	}
// 	else if ((len == 2 && (rel_path[0] == '.' && rel_path[1] == '.')))
// 	{
// 		ft_move_backwards_one(envp);
// 	}
// 	else
// 	{
// 		if (ft_isalpha(rel_path[0]))
// 		{
// 			ft_move_forward(rel_path, envp);
// 		}
// 		else
// 		{
// 			ft_move_backwards(rel_path, envp);
// 		}
// 	}
// 	return (0);
// }

// //se é un path relativo: 
// //verso dietro-> capire di quante cartelle bisogna andare indietro e poi chiamare chdir con il percorso assoluto modificato
// //verso avanti-> fare la strjoin con il pwd attuale e aggiungere la cartella in cui si vuole entrare

// //se é un path assoluto mandarlo direttamente a chdir

// //in caso di successo aggiornare la variabile pwd dell env
// char	*ft_cd(t_list *head, t_list **envp, int cmd_num)
// {
// 	char	*prev_dir;
// 	int		chdir_res;
// 	int 	i;

// 	if (cmd_num != 1)
// 	{
// 		ft_printf("cd con altri comandi non fa nulla perciò return\n");
// 		return (0);
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (head->cmd_m[i])
// 		{
// 			ft_printf("%i\n", i);
// 			i++;
// 		}
// 		if (i > 2) //se ci sono piú di due argomenti cd fallisce
// 		{
// 			ft_printf("cd: string not in pwd: %s\n", head->cmd_m[2]);
// 		}
// 		else
// 		{
// 			if (head->cmd_m[1][0] == '/')
// 			{
// 				ft_absolute_path(head->cmd_m[1], envp);
// 			}
// 			else if (head->cmd_m[1][0] == '.' || ft_isalpha(head->cmd_m[1][0]))
// 			{
// 				ft_relative_path(head->cmd_m[1], ft_strlen(head->cmd_m[1]), envp);
// 			}
// 		}
// 		return (prev_dir);
// 	}
// }

int g_exit_status;

void	cd_path(t_list **envp)
{
	t_list	*env;

	env = *envp;
	while (env)
	{
		if (!ft_strncmp(env->key, "PWD", 3))
		{
			free(env->value);
			env->value = getcwd(NULL, 0);
		}
		env = env->next;
	}
}

int	ft_cd(t_list *head, t_list **envp)
{
	char	*tmp;
	int		len;

	len = ft_count_rows(head->cmd_m);
	if (len == 1)
	{
		tmp = getenv("HOME");
		chdir(tmp);
		cd_path(envp);
		return (0);
	}
	else if (head->cmd_m[1] != NULL && head->cmd_m[1][0] == '~')
	{
		tmp = getenv("HOME");
		chdir(tmp);

		if (chdir(head->cmd_m[1] + 2) == -1)
			ft_printf("chdir fallito colione\n");
		cd_path(envp);
	}
	else if (chdir(head->cmd_m[1]) == -1)
	{
		//g_exit_status = 1;
		printf("cd: |%s|: error_palle", head->cmd_m[1]);
		printf("\n");
		return (1);
	}
	else
		cd_path(envp);
	return (0);
}
