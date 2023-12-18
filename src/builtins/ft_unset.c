/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:52:46 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 19:42:47 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

void	ft_unset_var(char *var, char **envp)
{
	int		i;
	int		j;
	size_t	len;

	i = -1;
	len = ft_strlen(var);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
		{
			free(envp[i]);
			j = i;
			while (envp[++j])
				envp[j - 1] = envp[j];
			envp[j - 1] = NULL;
			return ;
		}
	}
}

int	ft_unset(t_std_cmd *std_cmd, char **envp)
{
	int		i;

	g_status = 0;
	if (ft_strs_len(std_cmd->args) > 1)
	{
		i = -1;
		while (std_cmd->args[++i])
			ft_unset_var(std_cmd->args[i], envp);
	}
	else
		ft_raise_error("Not enough arguments");
	close_in_out(std_cmd->in_file, std_cmd->out_file);
	return (TRUE);
}
