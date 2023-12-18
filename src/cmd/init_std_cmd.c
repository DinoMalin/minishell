/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprigent <gprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:54:36 by jcario            #+#    #+#             */
/*   Updated: 2023/12/15 20:17:21 by gprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

t_std_cmd	ft_init_std_cmd(int index, int len)
{
	t_std_cmd	result;

	result.args = malloc(sizeof(char *));
	result.args[0] = NULL;
	result.path = NULL;
	result.in_file = -1;
	result.out_file = -1;
	if (index == 0)
		result.in_file = STDIN_FILENO;
	if (index == len - 1)
		result.out_file = STDOUT_FILENO;
	result.is_last = FALSE;
	return (result);
}
