/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:16:49 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 19:42:33 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

int	ft_exit(t_cmd *cmd, t_std_cmd *std_cmd)
{
	int	exit_code;

	if (ft_strs_len(std_cmd->args) == 1)
	{
		free_strs(cmd->envp);
		ft_free_cmd(cmd);
		exit(0);
	}
	else if (ft_strs_len(std_cmd->args) == 2)
	{
		exit_code = ft_atoi(std_cmd->args[1]);
		free_strs(cmd->envp);
		ft_free_cmd(cmd);
		exit(exit_code);
	}
	else
		ft_raise_error("Too many arguments");
	close_in_out(std_cmd->in_file, std_cmd->out_file);
	return (TRUE);
}
