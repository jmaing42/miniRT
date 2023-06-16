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

static t_minirt_args_parameter_string	*find(
	t_minirt_args_state *state,
	t_minirt_args_options_string *option
)
{
	t_minirt_args_parameter_string *const	array = state->params_string->array;
	size_t									i;

	i = -1;
	while (++i < state->params_string->length)
		if (array[i].option == option)
			return (&array[i]);
	return (NULL);
}

static t_err	append(t_minirt_args_state *mut_state, const char *value)
{
	t_minirt_args_parameter_string		new_entry;

	if (minirt_strdup(value, &new_entry.value))
		return (true);
	new_entry.option = mut_state->state_value.string;
	if (minirt_array_builder_append(mut_state->params_string, 1, &new_entry))
	{
		free(new_entry.value);
		return (true);
	}
	mut_state->state_type = MINIRT_ARGS_STATE_ANYTHING;
	return (false);
}

static t_err	replace(
	t_minirt_args_state *mut_state,
	t_minirt_args_parameter_string *entry,
	const char *value,
	bool need_replace
)
{
	char	*new_value;

	if (need_replace)
	{
		if (minirt_strdup(value, &new_value))
			return (true);
		free(entry->value);
		entry->value = new_value;
	}
	mut_state->state_type = MINIRT_ARGS_STATE_ANYTHING;
	return (false);
}

t_err	minirt_args_next_string(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	t_minirt_args_options_string *const	option = mut_state->state_value.string;
	t_minirt_args_parameter_string		*entry;

	(void)options;
	entry = find(mut_state, option);
	if (entry && (option->on_duplicate
			== MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_ERROR || (
				!minirt_str_eq(entry->value, arg) && option->on_duplicate
				== MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_IGNORE_IF_SAME
			)))
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER_STRING;
		mut_state->error.value.duplicate_parameter_string.option = option;
		return (false);
	}
	if (entry)
		return (append(mut_state, arg));
	return (replace(
			mut_state,
			entry,
			arg,
			option->on_duplicate
			== MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_STRING_USE_LAST
		));
}
