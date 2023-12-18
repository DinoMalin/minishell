/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprigent <gprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:25:23 by gprigent          #+#    #+#             */
/*   Updated: 2023/12/18 04:37:10 by gprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

t_parse	*ft_init_parse(void)
{
	t_parse		*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->start = 0;
	parse->size = 0;
	parse->single_quote = 0;
	parse->double_quote = 0;
	parse->i = 0;
	return (parse);
}

void	ft_update_quotes(char c, int *single_quote, int *double_quote)
{
	if (c == '\'' && !(*double_quote))
		*single_quote = !(*single_quote);
	else if (c == '"' && !(*single_quote))
		*double_quote = !(*double_quote);
}

void	ft_parse_operator(char *str, t_parse *parse)
{
	if (parse->size)
		parse->output[parse->i++] = ft_substr(str, parse->start, parse->size);
	if (ft_strncmp(&str[parse->start + parse->size], "<<", 2) == 0)
	{
		parse->output[parse->i++] = ft_strdup("<<");
		parse->start += parse->size + 3;
	}
	else if (ft_strncmp(&str[parse->start + parse->size], ">>", 2) == 0)
	{
		parse->output[parse->i++] = ft_strdup(">>");
		parse->start += parse->size + 3;
	}
	else
	{
		parse->output[parse->i++] = ft_strdup((char []){str
			[parse->start + parse->size], '\0'});
		parse->start += parse->size + 1;
	}
	parse->size = 0;
}

void	ft_split_words(char *str, t_parse *parse)
{
	if (ft_strchr("'\"", str[parse->start + parse->size]))
		ft_update_quotes(str[parse->start + parse->size],
			&parse->single_quote, &parse->double_quote);
	if (ft_strchr("|<>", str[parse->start + parse->size])
		&& !parse->single_quote && !parse->double_quote)
		ft_parse_operator(str, parse);
	else
		parse->size++;
}

char	**ft_split_cmd_str(char *str)
{
	t_parse		*parse;
	char		**output;

	parse = ft_init_parse();
	parse->output = malloc(ft_strlen(str) * sizeof(char *));
	while (str[parse->start + parse->size])
	{
		parse->start += parse->size;
		while (str[parse->start] == ' ' && str[parse->start])
			parse->start++;
		parse->size = 0;
		while ((str[parse->start + parse->size] != ' ' || parse->single_quote
				|| parse->double_quote) && str[parse->start + parse->size])
			ft_split_words(str, parse);
		if (parse->size)
			parse->output[parse->i++] = ft_substr(str, parse->start,
					parse->size);
	}
	parse->output[parse->i] = NULL;
	output = parse->output;
	free(parse);
	return (output);
}
