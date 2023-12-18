/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 03:48:53 by gprigent          #+#    #+#             */
/*   Updated: 2023/12/18 21:14:08 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

void	ft_free_std_cmd(t_std_cmd *std_cmd)
{
	int	i;

	i = -1;
	if (std_cmd->path)
		free(std_cmd->path);
	if (std_cmd->path == std_cmd->args[0])
		i = 0;
	if (std_cmd->args)
	{
		while (std_cmd->args[++i])
			free(std_cmd->args[i]);
		free(std_cmd->args);
	}
}

int	ft_free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd)
	{
		i = -1;
		while (++i < cmd->nb_std_cmds)
			ft_free_std_cmd(&cmd->std_cmds[i]);
		free(cmd->std_cmds);
		free(cmd);
	}
	return (0);
}

int	free_strs(char **strs)
{
	int	i;

	i = -1;
	if (strs)
	{
		while (strs[++i])
			free(strs[i]);
		free(strs);
	}
	return (0);
}

int	is_only_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			return (FALSE);
	return (TRUE);
}
