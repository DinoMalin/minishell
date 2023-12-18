/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:51:49 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 19:42:23 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

int	ft_echo(t_std_cmd *std_cmd)
{
	int	i;
	int	newline;

	if (ft_strs_len(std_cmd->args) > 1)
	{
		i = !ft_strncmp(std_cmd->args[1], "-n", 3);
		newline = i;
		while (std_cmd->args[++i])
		{
			if (i != newline + 1)
				ft_putchar_fd(' ', std_cmd->out_file);
			ft_putstr_fd(std_cmd->args[i], std_cmd->out_file);
		}
		if (!newline)
			ft_putchar_fd('\n', std_cmd->out_file);
	}
	else
		ft_putchar_fd('\n', std_cmd->out_file);
	close_in_out(std_cmd->in_file, std_cmd->out_file);
	g_status = 0;
	return (TRUE);
}
