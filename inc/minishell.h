/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:46:19 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/10 18:35:27 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../inc/libft.h"
# include "../inc/ft_printf.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>

# define ERR_NCMD 0
# define ERR_QUOTE 1
# define MALLOCERR 2
# define ENVERR 3
# define ACCESSERR 4
# define PATHERR 5
# define READLINEERR 6
# define ERR_INPUT 7
# define NODE_NUM 90

int	exit_status;

typedef struct s_miniflags
{
	bool	pipe;
	bool	red_i;
	bool	red_o;
	bool	read_i;
	bool	append_o;
	bool	s_quote;
	bool	d_quote;
}	t_miniflags;

typedef struct s_minishell
{
	int		exit_status; // serve a controllare se la shell deve essere ancora in esecuzione (vedi while nel main)
	char	*input; // qui viene storato l'input originale dell'utente
	char	**full_cmd; // qui l'input viene splittato in un array per essere gestito
	t_list	*envp_list;
	t_list	*cmd_list;
}	t_minishell;

//function to check and manipulate the input read from readline
int		ft_parser(t_minishell **minip, t_miniflags **minif);
int		ft_input_checker(char	*input);
int		ft_is_escaped(char	c);
t_list	*ft_create_list(t_list **cmd_list, char **full_cmd);

//building functions
t_minishell *ft_get_mini(t_minishell *mini);
t_minishell *ft_load_envp(t_minishell **minip, char **envp);
t_minishell *ft_mini_constructor(t_minishell **mini, t_miniflags **miniflags, char **envp);

//error
int	ft_perror(int err, char *cmd);

//builtins
int		is_builtin(t_list *head, t_list **envp, int **pipes, int index, int cmd_num);
int		ft_echo(t_list *head, int **pipes, int index, int cmd_num);
char	*ft_cd(t_list *head, t_list **envp, int cmd_num);
int		ft_pwd(char **cmd_m, int **pipes, int index);
int		ft_export(t_list *head, t_list **envp, int **pipes, int index);
int		ft_unset(t_list *head, t_list **envp, char *var);
void 	ft_delete_node(t_list **head, t_list *node_to_delete);
int		ft_env(t_list **envp, int **pipes, int index, char **cmd_m);

//without the proto of this func readline does not work
void	rl_replace_line(const char *text, int clear_undo);


//malloc & free
void    *ft_malloc_stuff(int n);

//executing commands
int ft_start_executing(t_list	**cmd_list, int cmd_num, t_list **envp);
int		ft_exec_cmd(t_list	*head, int cmd_num);

//signals
void	ft_CTRL_C_handler(int signum);
void	ft_CTRL_D_handler(int signum);
void	ft_CTRL_S_handler(int signum);
void	ft_sig_handler(int signum, siginfo_t *info, void *ucontext);


//dollar expander
char	*ft_dollar_expander(t_list **envp, char *str);
char    *ft_expander_helper(t_minishell **mini, char *input);
char    *ft_expander_finder(t_minishell **minip, int i, char *input);
char	*ft_dollar_starter(t_list **envp, char  *str, int i);

//utils
void		ft_execute_mini(t_minishell **mini, t_miniflags **minif);
int			ft_strerr(char *str);
size_t 		ft_smaller_string(char *str1, char *str2);
char		**ft_split_variant(char *s);
char		**ft_old_split(char const *s, char c);
int			old_count_w(char *str, char c);
char		**old_fill_m(const char *s, char c, char	**matrix, int num_w);
int			ft_count_commands(t_list **cmd_list);

//free
void		ft_lst_delete(t_list **stack);
int			free_stuff(t_list *node, char **matrix, t_list **stack, t_miniflags *flags);

//attributes management
void		ft_set_attributes(t_minishell **minip, t_miniflags **minif);

#endif