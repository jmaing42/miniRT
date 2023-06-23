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

#include "minirt/common/array_builder.h"

static bool	already_has(t_minirt_args_state *mut_state)
{
	t_minirt_args_parameter_boolean *const	array
		= mut_state->params_boolean->array;
	size_t									i;

	i = -1;
	while (++i < mut_state->params_boolean->length)
		if (array[i].option == mut_state->state_value.boolean)
			return (true);
	return (false);
}

static t_err	add(t_minirt_args_state *mut_state, bool value)
{
	const t_minirt_args_options_boolean *const	option
		= mut_state->state_value.boolean;
	const t_minirt_args_parameter_boolean		node = {option, value};

	if (minirt_array_builder_append(mut_state->params_boolean, 1, &node))
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_MALLOC_FAILURE;
		return (true);
	}
	return (false);
}

t_err	minirt_args_add_boolean(
	t_minirt_args_state *mut_state,
	bool value
)
{
	const t_minirt_args_options_boolean *const	option
		= mut_state->state_value.boolean;

	if (already_has(mut_state) && (option->on_duplicate
			== MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_BOOLEAN_ERROR))
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER_BOOLEAN;
		mut_state->error.value.duplicate_parameter_boolean.option = option;
	}
	return (add(mut_state, value));
}
