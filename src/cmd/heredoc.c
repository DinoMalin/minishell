/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:37:48 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 20:45:19 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

char	*get_heredoc(char *heredoc)
{
	char	*result;
	char	*line;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (1)
	{
		line = readline("heredoc> ");
		if (g_status == 130)
			break ;
		if (!line || g_status == 130
			|| (!ft_strncmp(line, heredoc, ft_strlen(line))
				&& ft_strlen(line)))
		{
			if (!line)
				ft_putchar_fd('\n', 1);
			break ;
		}
		result = ft_strjoin_free(result, ft_strjoin_free(line, "\n", 1), 2);
	}
	if (line)
		free(line);
	return (result);
}

int	run_heredoc(char *heredoc)
{
	int		pipe_fd[2];
	char	*heredoc_result;

	if (pipe(pipe_fd) == -1)
	{
		ft_raise_error("Pipe problem.");
		return (-1);
	}
	heredoc_result = get_heredoc(heredoc);
	write(pipe_fd[1], heredoc_result, ft_strlen(heredoc_result));
	free(heredoc_result);
	close(pipe_fd[1]);
	if (g_status == 130)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}
