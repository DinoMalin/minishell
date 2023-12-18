/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_std_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:43:47 by jcario            #+#    #+#             */
/*   Updated: 2023/12/17 22:45:7 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

static int	open_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		ft_raise_error(strerror(errno));
	return (fd);
}

static int	open_write(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		ft_raise_error(strerror(errno));
	return (fd);
}

static int	open_read(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_raise_error(strerror(errno));
	return (fd);
}

t_std_cmd	*ft_get_std_cmds(char **split_cmd, int len)
{
	int			i;
	int			j;
	t_std_cmd	*output;

	output = malloc(len * sizeof(t_std_cmd));
	output[0] = ft_init_std_cmd(0, len);
	i = -1;
	j = 0;
	while (split_cmd[++i])
	{
		if (!ft_strncmp("<<", split_cmd[i], 3) && split_cmd[i + 1])
			output[j].in_file = run_heredoc(split_cmd[++i]);
		else if (!ft_strncmp(">>", split_cmd[i], 3) && split_cmd[i + 1])
			output[j].out_file = open_append(split_cmd[++i]);
		else if (!ft_strncmp("<", split_cmd[i], 2) && split_cmd[i + 1])
			output[j].in_file = open_read(split_cmd[++i]);
		else if (!ft_strncmp(">", split_cmd[i], 2) && split_cmd[i + 1])
			output[j].out_file = open_write(split_cmd[++i]);
		else if (!ft_strncmp("|", split_cmd[i], 2) && ++j)
			output[j] = ft_init_std_cmd(j, len);
		else
			output[j].args = ft_join_matrix(output[j].args, split_cmd[i]);
	}
	free_strs(split_cmd);
	return (output);
}
