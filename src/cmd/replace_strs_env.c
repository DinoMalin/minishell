/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_strs_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprigent <gprigent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:34:58 by gprigent          #+#    #+#             */
/*   Updated: 2023/12/18 18:42:06 by gprigent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kregin.h"

extern int	g_status;

t_replace_env	*ft_init_replace_env(void)
{
	t_replace_env	*output;

	output = malloc(sizeof(t_replace_env));
	output->start = 0;
	output->size = 0;
	output->single_quote = 0;
	output->double_quote = 0;
	output->tmp_single_quote = 0;
	output->tmp_double_quote = 0;
	output->output = ft_strdup("");
	return (output);
}

void	ft_add_env(char *str, t_replace_env *replace_env, char **envp)
{
	replace_env->output = ft_strjoin_free(replace_env->output,
			ft_substr(str, replace_env->start, replace_env->size), 2);
	replace_env->start += replace_env->size + 1;
	replace_env->size = 0;
	while (ft_isalnum(str[replace_env->start + replace_env->size]))
		replace_env->size++;
	replace_env->tmp = ft_substr(str, replace_env->start, replace_env->size);
	if (!ft_strncmp(&str[replace_env->start], "?", 2))
	{
		replace_env->output = ft_strjoin_free(replace_env->output,
				ft_itoa(g_status), 2);
		replace_env->size++;
	}
	else if (ft_getenv(envp, replace_env->tmp))
		replace_env->output = ft_strjoin_free(replace_env->output,
				ft_getenv(envp, replace_env->tmp), 1);
	free(replace_env->tmp);
	replace_env->start += replace_env->size;
	replace_env->size = 0;
}

void	ft_delete_quotes(char *str, t_replace_env *replace_env)
{
	replace_env->tmp_single_quote = replace_env->single_quote;
	replace_env->tmp_double_quote = replace_env->double_quote;
	ft_update_quotes(str[replace_env->start + replace_env->size],
		&replace_env->single_quote, &replace_env->double_quote);
	if (((replace_env->single_quote || replace_env->tmp_single_quote)
			&& str[replace_env->start + replace_env->size] == '\'')
		|| ((replace_env->double_quote || replace_env->tmp_double_quote)
			&& str[replace_env->start + replace_env->size] == '"'))
	{
		replace_env->output = ft_strjoin_free(replace_env->output,
				ft_substr(str, replace_env->start++, replace_env->size), 2);
		replace_env->start += replace_env->size;
		replace_env->size = 0;
	}
	else
		replace_env->size++;
}

char	*ft_replace_str_env(char *str, char **envp)
{
	t_replace_env	*replace_env;
	char			*tmp;

	replace_env = ft_init_replace_env();
	while (str[replace_env->start + replace_env->size])
	{
		if (ft_strchr("'\"", str[replace_env->start + replace_env->size]))
			ft_delete_quotes(str, replace_env);
		else if (str[replace_env->start + replace_env->size] == '$'
			&& !replace_env->single_quote)
			ft_add_env(str, replace_env, envp);
		else
			replace_env->size++;
	}
	replace_env->output = ft_strjoin_free(replace_env->output,
			ft_substr(str, replace_env->start, replace_env->size), 2);
	tmp = replace_env->output;
	free(replace_env);
	return (tmp);
}

void	ft_replace_strs_env(char **strs, char **envp)
{
	int		i;
	char	*tmp;

	i = -1;
	while (strs[++i])
	{
		tmp = ft_replace_str_env(strs[i], envp);
		free(strs[i]);
		strs[i] = tmp;
	}
}
