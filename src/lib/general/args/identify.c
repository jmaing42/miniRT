/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_file_name (file name is useless too)          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42header-remover <whatever@example.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by file history     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_internal.h"

static bool	is_first_parameter_char(char ch)
{
	return (
		('a' <= ch && ch <= 'z' )
		|| ('A' <= ch && ch <= 'Z' )
	);
}

static bool	is_parameter_char(char ch)
{
	return (
		ch == '-'
		|| ('0' <= ch && ch <= '9' )
		|| is_first_parameter_char(ch)
	);
}

static t_minirt_args_type	identify_short(
	const char *arg
)
{
	if (!is_first_parameter_char(arg[0]))
		return (MINIRT_ARGS_TYPE_MALFORMED_PARAMETER);
	else
		return (MINIRT_ARGS_TYPE_SHORT);
}

static t_minirt_args_type	identify_long(
	const char *arg
)
{
	const char	*tmp;

	if (!is_first_parameter_char(arg[0]))
		return (MINIRT_ARGS_TYPE_MALFORMED_PARAMETER);
	tmp = arg;
	while (*++tmp)
	{
		if (is_parameter_char(*tmp))
			continue ;
		if (*tmp != '=')
			return (MINIRT_ARGS_TYPE_MALFORMED_PARAMETER);
		return (
			MINIRT_ARGS_TYPE_LONG_STRING_WITH_VALUE_OR_LONG_BOOLEAN_WITH_VALUE
		);
	}
	return (MINIRT_ARGS_TYPE_LONG_WITHOUT_VALUE);
}

t_minirt_args_type	minirt_args_identify(
	const char *arg
)
{
	if (arg[0] != '-')
		return (MINIRT_ARGS_TYPE_ARG);
	if (arg[1] != '-')
		return (identify_short(arg + 1));
	else
		return (identify_long(arg + 2));
}
