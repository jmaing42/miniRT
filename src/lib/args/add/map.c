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

typedef t_minirt_args_parameter_map_builder	t_builder;

static t_builder	*get_or_create_entry_builder(
	t_minirt_args_state *mut_state,
	const char *name
)
{
	size_t		i;
	t_builder	new_node;

	i = -1;
	while (++i < mut_state->params_map->length)
		if (minirt_str_eq(((t_builder *)
					mut_state->params_map->array)[i].parameter_name, name))
			return (&((t_builder *)mut_state->params_map->array)[i]);
	if (minirt_strdup(name, &new_node.parameter_name))
		return (NULL);
	new_node.builder
		= minirt_array_builder_new(sizeof(t_minirt_args_map_entry));
	if (!new_node.builder)
	{
		free(new_node.parameter_name);
		return (NULL);
	}
	if (minirt_array_builder_append(mut_state->params_map, 1, &new_node))
	{
		free(new_node.parameter_name);
		minirt_array_builder_free(new_node.builder);
		return (NULL);
	}
	return (&((t_builder *)
			mut_state->params_map->array)[mut_state->params_map->length - 1]);
}

static t_minirt_args_map_entry	*get_entry(
	t_minirt_array_builder *builder,
	const char *key
) {
	t_minirt_args_map_entry *const	entries = builder->array;
	size_t							i;

	i = -1;
	while (++i < builder->length)
		if (minirt_str_eq(entries[i].key, key))
			return (&entries[i]);
	return (NULL);
}

t_err	minirt_args_add_map(
	t_minirt_args_state *mut_state,
	t_minirt_args_options_map *option,
	char *key,
	char *value
)
{
	t_builder *const		entry_builder
		= get_or_create_entry_builder(mut_state, mut_state->state_value);
	t_minirt_args_map_entry	*entry;
	t_minirt_args_map_entry	tmp;

	if (!entry_builder)
	{
		free(key);
		free(value);
		return (true);
	}
	entry = get_entry(entry_builder->builder, key);
	if ((entry
			&& option->on_duplicate == MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_ERROR)
		|| (entry && !minirt_str_eq(value, entry->value) && option
			->on_duplicate == MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_IGNORE_IF_SAME))
	{
		free(value);
		mut_state->state_type = MINIRT_ARGS_STATE_ERROR;
		free(mut_state->state_value);
		mut_state->error.type = MINIRT_ARGS_ERROR_DUPLICATE_KEY;
		mut_state->error.value.duplicate_key.key = key;
		mut_state->error.value.duplicate_key.option = option;
		return (false);
	}
	if (!entry)
		entry = &tmp;
	tmp.key = key;
	tmp.value = value;
	// TODO:
}
