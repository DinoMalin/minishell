/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:13:40 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 19:42:28 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

int	ft_env(t_std_cmd *std_cmd, char **envp)
{
	int	i;

	g_status = 0;
	if (ft_strs_len(std_cmd->args) == 1)
	{
		i = -1;
		while (envp[++i])
			ft_putendl_fd(envp[i], 1);
	}
	else
		ft_raise_error("Too many arguments");
	close_in_out(std_cmd->in_file, std_cmd->out_file);
	return (TRUE);
}
