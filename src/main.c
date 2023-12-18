/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:26:49 by gprigent          #+#    #+#             */
/*   Updated: 2023/12/18 21:33:47 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

int	g_status;

void	ft_raise_error(char *error)
{
	g_status = 1;
	printf("%sError:%s %s\n", RED, END, error);
}

int	is_exec(int value)
{
	static int	is_exec = 0;

	if (value >= 0)
		is_exec = value;
	return (is_exec);
}

void	signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		g_status = 130;
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		if (!is_exec(-1))
			rl_redisplay();
	}
}

char	*ft_read_cmd(void)
{
	char	*prompt;
	char	*cmd_str;

	prompt = ft_get_prompt();
	if (!prompt)
		return (NULL);
	cmd_str = readline(prompt);
	free(prompt);
	if (!cmd_str)
		return (NULL);
	return (cmd_str);
}

int	main(int ac, char **av, char **envp)
{
	static char		*cmd_str = NULL;
	static t_cmd	*cmd = NULL;
	static char		**envp_cpy = NULL;

	(void) ac;
	(void) av;
	header();
	envp_cpy = ft_strs_cpy(envp);
	while (TRUE)
	{
		cmd_str = ft_read_cmd();
		if (!cmd_str)
			break ;
		add_history(cmd_str);
		if (!is_only_spaces(cmd_str))
		{
			cmd = ft_init_cmd(cmd_str, envp_cpy);
			if (!cmd)
				ft_raise_error(strerror(errno));
			ft_exec_cmd(cmd);
			ft_free_cmd(cmd);
		}
		free(cmd_str);
	}
	return (free(cmd_str), free_strs(envp_cpy));
}
