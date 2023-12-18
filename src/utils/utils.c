/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 23:55:13 by dropnod           #+#    #+#             */
/*   Updated: 2023/12/18 20:47:46 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

void	free_matrix(char **matrix, int start)
{
	while (matrix[start])
		free(matrix[start++]);
	free(matrix);
}

char	*ft_strsjoin(char **strs)
{
	int		i;
	int		strs_len;
	char	*output;

	i = -1;
	strs_len = 0;
	while (strs[++i])
		strs_len += ft_strlen(strs[i]);
	i = -1;
	output = ft_strdup("");
	if (!output)
		return (NULL);
	while (strs[++i])
		output = ft_strjoin_free(output, strs[i], 2);
	return (output);
}

int	ft_strs_len(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

char	**ft_strs_cpy(char **strs)
{
	int		i;
	int		j;
	char	**output;

	i = -1;
	output = malloc((ft_strs_len(strs) * 20) * sizeof(char *));
	if (!output)
		return (NULL);
	while (strs[++i])
	{
		j = -1;
		output[i] = malloc((ft_strlen(strs[i]) + 1) * sizeof(char));
		if (!output[i])
			return (NULL);
		while (strs[i][++j])
			output[i][j] = strs[i][j];
		output[i][j] = strs[i][j];
	}
	output[i] = strs[i];
	return (output);
}

char	**ft_join_matrix(char **s1, char *s2)
{
	char	**result;
	int		len;
	int		i;

	len = ft_strs_len(s1);
	i = 0;
	result = malloc((len + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = ft_strdup(s1[i]);
		free(s1[i]);
		i++;
	}
	result[i++] = ft_strdup(s2);
	result[i] = NULL;
	free(s1);
	return (result);
}
