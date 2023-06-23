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

static bool	already_has(
	t_minirt_args_state *mut_state,
	const t_minirt_args_options_boolean *option
)
{
	t_minirt_args_parameter_boolean *const	array
		= mut_state->params_boolean->array;
	size_t									i;

	i = (size_t)-1;
	while (++i < mut_state->params_boolean->length)
		if (array[i].option == option)
			return (true);
	return (false);
}

static t_err	add(
	t_minirt_args_state *mut_state,
	const t_minirt_args_options_boolean *option
)
{
	const bool								already
		= already_has(mut_state, option);
	const t_minirt_args_parameter_boolean	node = {option, true};

	if (already && (option->on_duplicate
			== MINIRT_ARGS_OPTIONS_DUPLICATE_PARAMETER_BOOLEAN_ERROR))
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_DUPLICATE_PARAMETER_BOOLEAN;
		mut_state->error.value.duplicate_parameter_boolean.option = option;
		return (true);
	}
	if (already)
		return (false);
	if (minirt_array_builder_append(mut_state->params_boolean, 1, &node))
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_MALLOC_FAILURE;
		return (true);
	}
	return (false);
}

static t_err	fallback(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	if (options->unknown_parameter
		!= MINIRT_ARGS_OPTIONS_UNKNOWN_PARAMETER_IGNORE)
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_UNKNOWN_PARAMETER;
		mut_state->error.value.unknown_parameter.arg = arg;
		return (true);
	}
	return (false);
}

t_err	minirt_args_next_anything_short_boolean(
	t_minirt_args_state *mut_state,
	t_minirt_args_options *options,
	const char *arg
)
{
	const char	*c;
	size_t		i;
	bool		found;

	if (add(mut_state, mut_state->state_value.boolean))
		return (false);
	c = &arg[2] - 1;
	while (*++c)
	{
		i = (size_t)(-1);
		found = false;
		while (!found && ++i < options->boolean_parameter_count)
		{
			if (options->boolean_parameters[i].short_name == *c)
			{
				if (add(mut_state, &options->boolean_parameters[i]))
					return (false);
				found = true;
			}
		}
		if (!found && fallback(mut_state, options, arg))
			return (false);
	}
	return (false);
}
