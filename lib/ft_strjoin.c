/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:20:51 by dropnod           #+#    #+#             */
/*   Updated: 2023/12/17 13:08:42 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *str_1, const char *str_2)
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
	return (output);
}
