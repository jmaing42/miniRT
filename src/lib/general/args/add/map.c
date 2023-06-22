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

static t_minirt_args_parameter_map_builder	*get_or_create_entry_builder(
	t_minirt_args_state *mut_state,
	const t_minirt_args_options_map *option
)
{
	size_t								i;
	t_minirt_args_parameter_map_builder	new_node;

	i = (size_t)-1;
	while (++i < mut_state->params_map->length)
		if (((t_minirt_args_parameter_map_builder *)
				mut_state->params_map->array)[i].option == option)
			return (&((t_minirt_args_parameter_map_builder *)
					mut_state->params_map->array)[i]);
	new_node.option = option;
	new_node.builder
		= minirt_array_builder_new(sizeof(t_minirt_args_map_entry));
	if (!new_node.builder)
		return (NULL);
	if (minirt_array_builder_append(mut_state->params_map, 1, &new_node))
	{
		minirt_array_builder_free(new_node.builder);
		return (NULL);
	}
	return (&((t_minirt_args_parameter_map_builder *)
			mut_state->params_map->array)[mut_state->params_map->length - 1]);
}

static t_minirt_args_map_entry	*get_entry(
	t_minirt_array_builder *builder,
	const char *key
) {
	t_minirt_args_map_entry *const	entries = builder->array;
	size_t							i;

	i = (size_t)-1;
	while (++i < builder->length)
		if (minirt_str_eq(entries[i].key, key))
			return (&entries[i]);
	return (NULL);
}

static t_err	add_entry(
	t_minirt_args_state *mut_state,
	t_minirt_args_parameter_map_builder *entry_builder,
	char *key,
	const char *value
)
{
	t_minirt_args_map_entry	new_entry;

	new_entry.key = key;
	new_entry.value = value;
	if (minirt_array_builder_append(entry_builder->builder, 1, &new_entry))
	{
		free(key);
		return (true);
	}
	else
	{
		mut_state->state_type = MINIRT_ARGS_STATE_ANYTHING;
	}
	return (false);
}

static t_err	replace_entry(
	t_minirt_args_state *mut_state,
	t_minirt_args_map_entry *entry,
	const char *value,
	bool need_replace
)
{
	if (need_replace)
		entry->value = value;
	mut_state->state_type = MINIRT_ARGS_STATE_ANYTHING;
	return (false);
}

t_err	minirt_args_add_map(
	t_minirt_args_state *mut_state,
	char *key,
	const char *value
)
{
	const t_minirt_args_options_map *const		o = mut_state->state_value.map;
	t_minirt_args_parameter_map_builder *const	entry_builder
		= get_or_create_entry_builder(mut_state, o);
	t_minirt_args_map_entry						*entry;

	if (!entry_builder)
	{
		free(key);
		return (true);
	}
	entry = get_entry(entry_builder->builder, key);
	if ((entry && o->on_duplicate == MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_ERROR)
		|| (entry && !minirt_str_eq(value, entry->value) && o
			->on_duplicate == MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_IGNORE_IF_SAME))
		return (minirt_args_add_map_error_duplicate_key(mut_state, key));
	if (!entry)
		return (add_entry(mut_state, entry_builder, key, value));
	return (
		replace_entry(
			mut_state,
			entry,
			value,
			o->on_duplicate == MINIRT_ARGS_OPTIONS_DUPLICATE_KEY_USE_LAST
		)
	);
}
