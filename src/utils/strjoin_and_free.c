/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprigent <gprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:15:10 by dropnod           #+#    #+#             */
/*   Updated: 2023/12/18 00:38:23 by gprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *str_1, char *str_2, int nb_free)
{
	size_t	str_1_len;
	size_t	str_2_len;
	char	*output;

	str_1_len = ft_strlen(str_1);
	str_2_len = ft_strlen(str_2);
	output = malloc((str_1_len + str_2_len + 1) * sizeof(char));
	if (!output)
		return (NULL);
	ft_strlcpy(output, str_1, str_1_len + 1);
	ft_strlcat(output, str_2, str_1_len + str_2_len + 1);
	if (nb_free >= 1)
		free(str_1);
	if (nb_free >= 2)
		free(str_2);
	return (output);
}
