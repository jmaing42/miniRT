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

#include "minirt/common/array_builder.h"

static t_err	error(
	t_minirt_args_state *state,
	t_minirt_args_result *out
)
{
	minirt_args_state_deinit(state);
	out->type = MINIRT_ARGS_RESULT_ERROR;
	out->value.error = state->error;
	return (true);
}

static t_err	fail(
	t_minirt_args_state *state,
	t_minirt_args_result *out
)
{
	if (out->value.ok.args)
	{
		free(out->value.ok.args);
		if (out->value.ok.string)
		{
			free(out->value.ok.string);
			if (out->value.ok.map)
			{
				free(out->value.ok.map);
				if (out->value.ok.set)
				{
					free(out->value.ok.set);
					if (out->value.ok.boolean)
					{
						free(out->value.ok.boolean);
					}
				}
			}
		}
	}
	minirt_args_state_deinit(state);
	out->type = MINIRT_ARGS_RESULT_ERROR;
	out->value.error.type = MINIRT_ARGS_ERROR_MALLOC_FAILURE;
	return (true);
}

static t_err	ok(
	t_minirt_args_state *state,
	t_minirt_args_result *out
)
{
	out->value.ok.args = minirt_array_builder_build(state->args);
	out->value.ok.arg_count = state->args->length;
	if (!out->value.ok.args)
		return (fail(state, out));
	out->value.ok.string = minirt_array_builder_build(state->params_string);
	out->value.ok.string_count = state->params_string->length;
	if (!out->value.ok.string)
		return (fail(state, out));
	out->value.ok.map = minirt_array_builder_build(state->params_map);
	out->value.ok.map_count = state->params_map->length;
	if (!out->value.ok.map)
		return (fail(state, out));
	out->value.ok.set = minirt_array_builder_build(state->params_set);
	out->value.ok.set_count = state->params_set->length;
	if (!out->value.ok.set)
		return (fail(state, out));
	out->value.ok.boolean = minirt_array_builder_build(state->params_boolean);
	out->value.ok.boolean_count = state->params_boolean->length;
	if (!out->value.ok.boolean)
		return (fail(state, out));
	minirt_args_free_state_ok(state);
	out->type = MINIRT_ARGS_RESULT_OK;
	return (false);
}

t_err	minirt_args_finalize(
	t_minirt_args_state *mut_state,
	t_minirt_args_result *out
)
{
	if (mut_state->state_type == MINIRT_ARGS_STATE_STRING)
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_MISSING_VALUE_STRING;
		mut_state->error.value.missing_value_string.option
			= mut_state->state_value.string;
	}
	if (mut_state->state_type == MINIRT_ARGS_STATE_ENTRY)
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_MISSING_VALUE_MAP;
		mut_state->error.value.missing_value_map.option
			= mut_state->state_value.map;
	}
	if (mut_state->state_type == MINIRT_ARGS_STATE_VALUE)
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_MISSING_VALUE_SET;
		mut_state->error.value.missing_value_set.option
			= mut_state->state_value.set;
	}
	if (mut_state->state_type == MINIRT_ARGS_STATE_ERROR)
		return (error(mut_state, out));
	return (ok(mut_state, out));
}
