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

static t_minirt_args_parameter_set_builder	*get_or_create_entry_builder(
	t_minirt_args_state *mut_state,
	const t_minirt_args_options_set *option
)
{
	size_t								i;
	t_minirt_args_parameter_set_builder	new_node;

	i = (size_t)-1;
	while (++i < mut_state->params_set->length)
		if (((t_minirt_args_parameter_set_builder *)
				mut_state->params_set->array)[i].option == option)
			return (&((t_minirt_args_parameter_set_builder *)
					mut_state->params_set->array)[i]);
	new_node.option = option;
	new_node.builder
		= minirt_array_builder_new(sizeof(t_minirt_args_map_entry));
	if (!new_node.builder)
		return (NULL);
	if (minirt_array_builder_append(mut_state->params_set, 1, &new_node))
	{
		minirt_array_builder_free(new_node.builder);
		return (NULL);
	}
	return (&((t_minirt_args_parameter_set_builder *)
			mut_state->params_set->array)[mut_state->params_set->length - 1]);
}

static bool	has(
	t_minirt_array_builder *builder,
	const char *name
)
{
	char **const	entries = builder->array;
	size_t			i;

	i = (size_t)-1;
	while (++i < builder->length)
		if (minirt_str_eq(entries[i], name))
			return (true);
	return (false);
}

static t_err	append(
	t_minirt_array_builder *builder,
	const char *value
)
{
	return (minirt_array_builder_append(builder, 1, &value));
}

t_err	minirt_args_add_set(
	t_minirt_args_state *mut_state,
	const char *value
)
{
	const t_minirt_args_options_set *const		option
		= mut_state->state_value.set;
	t_minirt_args_parameter_set_builder *const	entry_builder
		= get_or_create_entry_builder(mut_state, option);
	const bool									duplicate
		= has(entry_builder->builder, value);

	if (duplicate
		&& option->on_duplicate == MINIRT_ARGS_OPTIONS_DUPLICATE_VALUE_ERROR)
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		mut_state->error.type = MINIRT_ARGS_ERROR_DUPLICATE_VALUE;
		mut_state->error.value.duplicate_value.option = option;
		mut_state->error.value.duplicate_value.value = value;
	}
	return (append(entry_builder->builder, value));
}
