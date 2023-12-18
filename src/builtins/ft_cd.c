/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:54:40 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 21:08:05 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

int	ft_cd(t_std_cmd *std_cmd)
{
	g_status = 0;
	if (ft_strs_len(std_cmd->args) == 2)
	{
		if (chdir(std_cmd ->args[1]) == -1)
			ft_raise_error("No such file or directory");
	}
	else
		ft_raise_error("Too many arguments");
	close_in_out(std_cmd->in_file, std_cmd->out_file);
	return (TRUE);
}
