/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:21:01 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 20:43:41 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

int	ft_exec_builtin(t_cmd *cmd, int i)
{
	if (!ft_strncmp("cd", cmd->std_cmds[i].args[0], 3))
		return (ft_cd(&cmd->std_cmds[i]));
	else if (!ft_strncmp("echo", cmd->std_cmds[i].args[0], 5))
		return (ft_echo(&cmd->std_cmds[i]));
	else if (!ft_strncmp("pwd", cmd->std_cmds[i].args[0], 4))
		return (ft_pwd(&cmd->std_cmds[i]));
	else if (!ft_strncmp("export", cmd->std_cmds[i].args[0], 7))
		return (ft_export(&cmd->std_cmds[i], cmd->envp));
	else if (!ft_strncmp("unset", cmd->std_cmds[i].args[0], 6))
		return (ft_unset(&cmd->std_cmds[i], cmd->envp));
	else if (!ft_strncmp("env", cmd->std_cmds[i].args[0], 4))
		return (ft_env(&cmd->std_cmds[i], cmd->envp));
	else if (!ft_strncmp("exit", cmd->std_cmds[i].args[0], 5))
		return (ft_exit(cmd, &cmd->std_cmds[i]));
	return (FALSE);
}

char	*ft_get_path(char *arg, char **envp)
{
	int		i;
	char	**paths;
	char	*result;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (!envp[i] || access(arg, X_OK) == 0)
		return (arg);
	paths = ft_split(&envp[i][5], ':');
	i = -1;
	while (paths[++i])
	{
		result = ft_strjoin_free(paths[i], "/", 1);
		result = ft_strjoin_free(result, arg, 1);
		if (access(result, X_OK) == 0)
		{
			while (paths[++i])
				free(paths[i]);
			free(paths);
			return (result);
		}
		free(result);
	}
	return (free(paths), NULL);
}

void	ft_process_child(t_std_cmd *std_cmd, char **envp)
{
	if (std_cmd->in_file != STDIN_FILENO)
	{
		if (dup2(std_cmd->in_file, STDIN_FILENO) == -1)
			ft_raise_error(strerror(errno));
		close(std_cmd->in_file);
	}
	if (std_cmd->out_file != STDOUT_FILENO)
	{
		if (dup2(std_cmd->out_file, STDOUT_FILENO) == -1)
			ft_raise_error(strerror(errno));
		close(std_cmd->out_file);
	}
	if (!std_cmd->is_last && std_cmd->in_file != STDIN_FILENO)
		close(std_cmd->in_file);
	execve(std_cmd->path, std_cmd->args, envp);
	ft_raise_error("Command not found");
	exit(1);
}

void	ft_run_pipe(t_std_cmd *std_cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_raise_error(strerror(errno));
	else if (pid == 0)
		ft_process_child(std_cmd, envp);
	else
	{
		std_cmd->pid = pid;
		waitpid(std_cmd->pid, &g_status, 0);
		if (std_cmd->in_file != 0)
			close(std_cmd->in_file);
		if (std_cmd->out_file != 1)
			close(std_cmd->out_file);
	}
}

void	ft_exec_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	is_exec(1);
	while (i < cmd->nb_std_cmds)
	{
		if (cmd->std_cmds[i].args[0] && !ft_exec_builtin(cmd, i)
			&& cmd->std_cmds[i].in_file != -1)
		{
			cmd->std_cmds[i].path = ft_get_path(cmd->std_cmds[i].args[0],
					cmd->envp);
			if (cmd->std_cmds[i].path)
				ft_run_pipe(&cmd->std_cmds[i], cmd->envp);
			else
				ft_raise_error("Command not found");
		}
		i++;
	}
	i = 0;
	while (i < cmd->nb_std_cmds)
	{
		if (cmd->std_cmds[i++].is_last)
			break ;
	}
	is_exec(0);
}
