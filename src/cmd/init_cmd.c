/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprigent <gprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:21:59 by gprigent          #+#    #+#             */
/*   Updated: 2023/12/18 18:44:03 by gprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

int	ft_count_std_cmd(char **split_cmd_str)
{
	int	i;
	int	output;

	i = -1;
	output = 1;
	while (split_cmd_str[++i])
		if (!ft_strncmp(split_cmd_str[i], "|", 2))
			output++;
	return (output);
}

static void	check_out_file(t_cmd *cmd, int i, int pipe_fd[2])
{
	if (cmd->std_cmds[i + 1].in_file == -1)
	{
		pipe(pipe_fd);
		cmd->std_cmds[i].out_file = pipe_fd[1];
		cmd->std_cmds[i + 1].in_file = pipe_fd[0];
	}
	else
	{
		pipe(pipe_fd);
		close(pipe_fd[0]);
		cmd->std_cmds[i].out_file = pipe_fd[1];
	}
}

void	set_fds(t_cmd *cmd)
{
	int	i;
	int	len;
	int	pipe_fd[2];

	i = 0;
	len = cmd->nb_std_cmds;
	while (i < len)
	{
		if (i == 0 && i == len)
			return ;
		if (i < len - 1 && cmd->std_cmds[i].out_file == -1)
			check_out_file(cmd, i, pipe_fd);
		else if (i < len - 1 && cmd->std_cmds[i].out_file != -1
			&& cmd->std_cmds[i + 1].in_file == -1)
		{
			pipe(pipe_fd);
			close(pipe_fd[1]);
			cmd->std_cmds[i + 1].in_file = pipe_fd[0];
		}
		i++;
	}
}

t_cmd	*ft_init_cmd(char *cmd_str, char **envp)
{
	t_cmd	*output;
	char	**split_cmd_str;

	output = malloc(sizeof(t_cmd));
	split_cmd_str = ft_split_cmd_str(cmd_str);
	if (!output || !split_cmd_str)
		return (NULL);
	ft_replace_strs_env(split_cmd_str, envp);
	output->nb_std_cmds = ft_count_std_cmd(split_cmd_str);
	output->std_cmds = ft_get_std_cmds(split_cmd_str, output->nb_std_cmds);
	output->envp = envp;
	set_fds(output);
	return (output);
}
