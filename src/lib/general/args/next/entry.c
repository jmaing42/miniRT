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

#include <stdlib.h>

#include "minirt/common/libc.h"
#include "minirt/common/array_builder.h"

static t_err	next(
	t_minirt_args_state *mut_state,
	const char *arg,
	size_t index
)
{
	char	*key;
	char	*value;

	value = NULL;
	if (!arg[index] && minirt_strdup(arg + index + 1, &value))
		return (true);
	if (minirt_strndup(arg, index, &key))
	{
		free(value);
		return (true);
	}
	return (minirt_args_add_map(mut_state, key, value));
}

t_err	minirt_args_next_entry(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	size_t						index;
	const bool					has_eq
		= minirt_strchr(arg, '=', &index);

	(void)options;
	if (!has_eq && !mut_state->state_value.map->allow_null)
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_MISSING_VALUE_MAP;
		mut_state->error.value.missing_value_map.option
			= mut_state->state_value.map;
		return (false);
	}
	return (next(mut_state, arg, index));
}
