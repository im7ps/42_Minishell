/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:46:19 by sgerace           #+#    #+#             */
/*   Updated: 2023/03/31 20:23:35 by sgerace          ###   ########.fr       */
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
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
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

extern int	g_exit_status;

typedef struct s_echo
{
	int	i;
	int	flag_index;
	int	len;
}	t_echo;

typedef struct s_xfillmv
{
	int		i;
	int		j;
	int		len;
	int		quotes;
	int		qcount;
	int		num_w;
	char	c;
}	t_xfillmv;

typedef struct s_xsubstr
{
	int	i;
	int	len;
}	t_xsubstr;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_minishell
{
	int			nopath;
	int			built_in_counter;
	int			cmd_num;
	int			index;
	int			flush;
	char		*input;
	char		**full_cmd;
	t_list		*envp_list;
	t_list		*cmd_list;
	t_list		*export_list;
	int			export_flag;
	t_garbage	*garbage;
	int			fd;
}	t_minishell;

bool		ft_char_red(char c);
void		ft_envp_initialize(t_list *new_node);
int			ft_cd(t_list *head, t_list **envp);
t_minishell	*ft_load_export(t_minishell **minip, char **envp);
void		ft_check_path(t_minishell **minip, t_list **envp);

//function to check and manipulate the input read from readline
int			ft_parser(t_minishell **minip);
int			ft_is_escaped(char c, int flag);
int			ft_input_checker(char	*input, bool onlytab);
t_list		*ft_create_list(t_minishell **minip, t_list **cmd_l, char **f_cmd);
int			ft_double_red_checker(char *input, bool redtoggle);

//building functions
t_minishell	*ft_load_envp(t_minishell **minip, char **envp);
void		ft_mini_initializer(t_minishell **mini, char **envp, int flag);

//error
int			ft_perror(int err, char *cmd);

//builtins
int			handle_command(t_minishell *mini, t_list *head, t_list **envp, int **pipes, int index, int cmd_num);
int			handle_builtin(t_minishell *mini, t_list *head, t_list **envp, int **pipes, int index);
int			ft_echo(t_list *head, int **pipes, int index);
int			ft_pwd(t_list *head, char **cmd_m, int **pipes, int index);
int			ft_export(t_minishell *mini, t_list *head);
int			ft_unset(t_list *head, t_list **envp, char *var, t_list **export_list);
void		ft_delete_node(t_list **head, t_list *node_to_delete);
int			ft_env(t_list **envp, int **pipes, int index, char **cmd_m);

//without the proto of this func readline does not work
void		rl_replace_line(const char *text, int clear_undo);

//get next line
char		*get_next_line(int fd, int buffer_size);
char		*read_and_join(int fd, char *dst, int buffer_size);
char		*get_line(char *buffer);
char		*store_extra_char(char	*buffer);

//redirection
char		**ft_delete_redirection(char **cmd_m);
int			ft_redirection_type(char **command);
int			ft_redirect_output(int **pipes, t_list *head, int i);
int			ft_append_output(int **pipes, t_list *head, int i);
int			ft_redirect_input(t_minishell *mini, t_list *head, int **pipes, int i);
void		ft_upload_redirection(t_list **cmd_list);
int			ft_is_redirection(char *str);

//malloc & free
void		*ft_malloc_stuff(int n);

//executing commands
int			ft_start_executing(t_minishell **minip, t_list **envp);
int			ft_execute_command(t_minishell *mini, int **pipes, t_list *head, int cmd_num, int index);
int			wait_for_execution(int cmd_num, int built_in_counter);
int			handle_non_builtin(t_minishell *mini, t_list *head, t_list **envp, int **pipes, int index, int cmd_num);

//signals
void		ft_ctrl_c_handler(int signum);
void		ft_ctrl_d_handler(int signum);
void		ft_ctrl_s_handler(int signum);
void		ft_sig_handler(int signum, siginfo_t *info, void *ucontext);

char		*ft_expander_helper(t_minishell **mini, char *input);
char		*ft_expander_finder(t_minishell **minip, int i, char *input);
char		*ft_dollar_expander(t_garbage **garbage, char *args, t_list *env);

//utils
void		ft_execute_mini(t_minishell **minip, char **envp);
char		**ft_split_variant(t_minishell *mini, char *s);
char		**ft_old_split(t_minishell **minip, char const *s, char c);
int			old_count_w(char *str, char c);
int			ft_set_exit_status(int value);
int			ft_count_commands(t_list **cmd_list);
char		*ft_trypath(t_minishell **minip, char	*cmd, t_list **envp);
int			ft_count_rows(char **cmd_m);
int			ft_update_quotes(char c);
bool		ft_define_squotes(char c);

//input utils
int			ft_input_checklist(t_minishell **minip, t_list **envp);
char		ft_whatis(char c);
int			ft_get_starting_shllv(t_list **envp);
int			ft_handle_shllv(t_minishell **minip);

//split utils
int			ft_get_word_length(const char *s, t_xfillmv *fmv);
void		ft_init_fmv(t_xfillmv *fmv);

//pipes
void		open_pipes(int **pipes, int cmd_num, t_garbage **garbage);
void		close_pipes(int **pipes, int cmd_num);

//free
void		ft_lst_delete(t_list **stack);

//attributes management
void		ft_set_attributes(t_minishell **minip);

//garbage collector
void		*gc_alloc(t_garbage **head, int size, int count);
void		ft_garbage_collector(t_garbage *head);
void		add_node(t_garbage **head, void *ptr);

//modified libft
char		*ft_substr_m(t_garbage **garbage, char const *s, t_xsubstr sub);
char		*ft_strdup_m(t_garbage **garbage, const char *s1);
char		*ftm_itoa(t_garbage **garbage, int n);
char		**ftm_split(t_garbage **garbage, char const *s, char c);
char		*ftm_strjoin(t_garbage **g, char const *s1, char const *s2, int f);
void		ft_init_fmv(t_xfillmv *fmv);
#endif