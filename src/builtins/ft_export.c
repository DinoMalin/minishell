/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:51:55 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 21:06:43 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

void	ft_export_var(char *var, char *name, char *value, char **envp)
{
	int		i;

	if (!name || !value)
		return ;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], name, ft_strlen(name))
			&& envp[i][ft_strlen(name)] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(var);
			free(name);
			free(value);
			return ;
		}
	}
	envp[i] = ft_strdup(var);
	envp[i + 1] = NULL;
	free(name);
	free(value);
}

void	ft_process_export(t_std_cmd *std_cmd, char **envp)
{
	int		i;
	int		j;
	char	*name;
	char	*val;

	i = 0;
	while (std_cmd->args[++i])
	{
		j = 0;
		while (std_cmd->args[i][j] != '=' && std_cmd->args[i][j])
			j++;
		name = ft_substr(std_cmd->args[i], 0, j);
		val = ft_substr(std_cmd->args[i], j, ft_strlen(std_cmd->args[i]));
		if (!name[0] || !val[0])
			(free(name), free(val));
		if (!name[0] || !val[0])
			continue ;
		ft_export_var(std_cmd->args[i], name, val, envp);
	}
}

int	ft_export(t_std_cmd *std_cmd, char **envp)
{
	g_status = 0;
	if (ft_strs_len(std_cmd->args) == 1)
		ft_env(std_cmd, envp);
	else
		ft_process_export(std_cmd, envp);
	return (close_in_out(std_cmd->in_file, std_cmd->out_file), TRUE);
}
