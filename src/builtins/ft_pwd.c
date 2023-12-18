/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:57:34 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 19:42:42 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

int	ft_pwd(t_std_cmd *std_cmd)
{
	char	*cwd;

	g_status = 0;
	if (ft_strs_len(std_cmd->args) == 1)
	{
		cwd = getcwd(NULL, 0);
		ft_putendl_fd(cwd, 1);
		free(cwd);
	}
	else
		ft_raise_error("Too many arguments");
	close_in_out(std_cmd->in_file, std_cmd->out_file);
	return (TRUE);
}
