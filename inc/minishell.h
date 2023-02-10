/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:46:19 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/10 22:05:39 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../inc/libft.h"
# include "../inc/ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>

# define ERR_NCMD 0
# define ERR_QUOTE 1
# define MALLOCERR 2
# define ENVERR 3
# define ACCESSERR 4
# define PATHERR 5
# define READLINEERR 6
# define ERR_INPUT 7
# define NODE_NUM 90

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
int		ft_lexer(t_minishell **minip, t_miniflags **minif);
int		ft_input_checker(char	*input);
int		ft_is_escaped(char	c);
void	ft_create_list(t_list **cmd_list, char **full_cmd);

//building functions
t_minishell *ft_get_mini(t_minishell *mini);
t_minishell *ft_load_envp(t_minishell **minip, char **envp);
t_minishell *ft_mini_constructor(t_minishell **mini, t_miniflags **miniflags, char **envp);

//error
int	ft_perror(int err, char *cmd);

//builtins
int	builtin(t_minishell *mini);

//without the proto of this func readline does not work
void	rl_replace_line(const char *text, int clear_undo);


//malloc & free
void    *ft_malloc_stuff(int n);
void	ft_free_stuff(t_minishell *mini, char *str);

//executing commands
int		ft_start_executing(t_list	**cmd_list);
int		ft_exec_cmd(t_list	*head, int cmd_num);

//signals
void	ft_CTRL_C_handler(int signum);
void	ft_CTRL_D_handler(int signum);
void	ft_CTRL_S_handler(int signum);
void	ft_sig_handler(int signum, siginfo_t *info, void *ucontext);


//dollar expander
char	*ft_dollar_expander(t_minishell **mini);
char    *ft_expander_helper(t_minishell **mini, char *input);
char    *ft_expander_finder(char *str, t_minishell **minip);
char	*ft_dollar_starter(t_minishell **minip, char  *str);

//utils
void		ft_execute_mini(t_minishell **mini, t_miniflags **minif);
int			ft_strerr(char *str);
size_t 		ft_smaller_string(char *str1, char *str2);
char		**ft_split_variant(char *s);

//attributes management
void		ft_attributes_management(t_minishell **minip, t_miniflags **minif);
void		ft_quotes_management(char	c, t_miniflags **minif);

#endif