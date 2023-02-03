/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:46:19 by sgerace           #+#    #+#             */
/*   Updated: 2023/02/03 16:44:55 by sgerace          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>

# define ERR_NCMD 0
# define ERR_QUOTE 1
# define MALLOCERR 2
# define ENVERR 3
# define ACCESSERR 4
# define PATHERR 5
# define READLINEERR 6
# define ERR_INPUT 7
# define NODE_NUM 90

typedef struct s_prompt
{
	const char *name;
	int 	pid;
	char 	**envp;
	t_list 	*cmds;
}	t_prompt;

typedef struct s_minishell
{
	int		exit_status; // serve a controllare se la shell deve essere ancora in esecuzione (vedi while nel main) [non funziona sto provando a fixare PD]
	char	*input; // qui viene storato l'input originale dell'utente
	char	**full_cmd; // qui l'input viene splittato in un array per essere gestito
	t_list	*cmd_list;
}	t_minishell;

//error
int	ft_perror(int err, char *cmd);

//builtins
int	builtin(t_minishell *mini);

//without the proto of this func readline does not work
// void	rl_replace_line(const char *text, int clear_undo);

//function to check and manipulate the input read from readline
int		ft_lexer(t_minishell *mini);
int		ft_check_special_char(char	*input);
int		ft_check_quotes(char	*input);
void	ft_create_list(t_list **cmd_list, char **full_cmd);

//malloc & free
void    	*ft_malloc_stuff(int n);
void		ft_free_stuff(t_minishell *mini, char *str);

//executing commands
int		ft_start_executing(t_list	**cmd_list);
int		ft_exec_cmd(t_list	*head, int cmd_num);

//signals
void		ft_CTRL_C_handler(int signum);
void		ft_CTRL_D_handler(int signum);
void		ft_CTRL_S_handler(int signum);
void		ft_sig_handler(int signum, siginfo_t *info, void *ucontext);

//utils
t_minishell *ft_get_mini(t_minishell *mini);
void		ft_execute_mini(t_minishell **mini);
int			ft_strerr(char *str);
int			ft_invalid_check(char *str);

#endif