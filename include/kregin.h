/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kregin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:35:24 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 20:44:00 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KREGIN_H
# define KREGIN_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>

# define ARENA_SIZE 10000

# define TRUE 1
# define FALSE 0

/* COLORS */
# define RED	"\033[31;1m"
# define GREEN	"\033[92;1m"
# define BLU	"\033[36;1m"
# define END	"\033[0m"

/* REDIRECTIONS */
# define PIPE		"|"
# define APPEND		">>"
# define OUT		">"
# define IN			"<"
# define HEREDOC	"<<"

/* STRUCTS */
typedef struct s_std_cmd
{
	char	*path;
	char	**args;
	int		in_file;
	int		out_file;
	int		is_last;
	pid_t	pid;
}	t_std_cmd;
t_std_cmd	ft_init_std_cmd(int index, int len);

typedef struct s_cmd
{
	int			nb_std_cmds;
	char		**envp;
	t_std_cmd	*std_cmds;
}	t_cmd;
t_cmd		*ft_init_cmd(char *cmd, char **envp);

typedef struct s_parse
{
	int		i;
	char	**output;
	int		start;
	int		size;
	int		single_quote;
	int		double_quote;
}	t_parse;

typedef struct s_replace_env
{
	int		start;
	int		size;
	int		single_quote;
	int		double_quote;
	int		tmp_single_quote;
	int		tmp_double_quote;
	char	*output;
	char	*tmp;
}	t_replace_env;

/* UTILS */
char		*ft_strsjoin(char **strs);
char		*ft_get_path(char *arg, char **envp);
void		ft_raise_error(char *error);
char		**ft_join_matrix(char **s1, char *s2);
char		**ft_strs_cpy(char **strs);
void		free_matrix(char **matrix, int start);
char		*ft_getenv(char **cmd, char *name);
void		close_in_out(int fd_in, int fd_out);

/* MAIN */
int			is_exec(int value);
void		signal_handler(int signal_number);
int			ft_exec_builtin(t_cmd *cmd, int i);
int			ft_strs_len(char **strs);
int			ft_free_cmd(t_cmd *cmd);
int			free_strs(char **strs);
int			is_only_spaces(char *str);

// ft_split_cmd_str.c
char		**ft_split_cmd_str(char *str);

/* PARSE */
char		*ft_get_prompt(void);
t_std_cmd	*ft_get_std_cmds(char **split_cmd_str, int len);
void		ft_replace_strs_env(char **strs, char **envp);
void		ft_update_quotes(char c, int *is_in_single_quote,
				int *is_in_double_quote);
char		*ft_strjoin_free(char *str_1, char *str_2, int nb_free);

/* EXECUTE */
void		ft_exec_cmd(t_cmd *env);
int			run_heredoc(char *heredoc);

/* BUILT-IN */
int			ft_echo(t_std_cmd *std_cmd);
int			ft_cd(t_std_cmd *std_cmd);
int			ft_pwd(t_std_cmd *std_cmd);
int			ft_exit(t_cmd *cmd, t_std_cmd *std_cmd);
int			ft_export(t_std_cmd *std_cmd, char **envp);
int			ft_unset(t_std_cmd *std_cmd, char **envp);
int			ft_env(t_std_cmd *std_cmd, char **envp);
void		header(void);

#endif