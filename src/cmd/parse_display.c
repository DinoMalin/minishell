/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprigent <gprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:11:51 by jcario            #+#    #+#             */
/*   Updated: 2023/12/18 00:40:29 by gprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

char	*ft_limit_prompt(char *prompt)
{
	char	*output;
	int		i;

	if (ft_strlen(prompt) <= 20)
		return (prompt);
	output = malloc(23 * sizeof(char));
	if (!output)
		return (prompt);
	output[22] = '.';
	output[21] = '.';
	output[20] = '.';
	i = -1;
	while (++i < 20)
		output[i] = prompt[i];
	free(prompt);
	return (output);
}

char	*ft_get_prompt(void)
{
	char	**dirs;
	char	*output;
	int		i;

	i = 0;
	output = getcwd(NULL, 0);
	dirs = ft_split(output, '/');
	free(output);
	while (dirs[i + 1] != NULL)
		i++;
	output = ft_strdup(dirs[i]);
	output = ft_limit_prompt(output);
	i = -1;
	while (dirs[++i])
		free(dirs[i]);
	free(dirs);
	if (g_status == 0)
		output = ft_strsjoin((char *[]){ft_strdup(GREEN), ft_strdup(" → "),
				ft_strdup(BLU), output, ft_strdup(" "), ft_strdup(END), NULL});
	else
		output = ft_strsjoin((char *[]){ft_strdup(RED), ft_strdup(" → "),
				ft_strdup(BLU), output, ft_strdup(" "), ft_strdup(END), NULL});
	return (output);
}
