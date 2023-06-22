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

#include "minirt/path.h"

#include <stdlib.h>

#include "minirt/common/libc.h"
#include "minirt/common/array_builder.h"

static void	free_builder(t_minirt_array_builder *builder)
{
	size_t	i;

	i = -1;
	while (++i < builder->length)
		free(((t_minirt_path_segment *)builder->array)[i].str);
	minirt_array_builder_free(builder);
}

static t_err	add_child_node(t_minirt_array_builder *builder, char *segment)
{
	const t_minirt_path_segment	node = {MINIRT_PATH_SEGMENT_CHILD, segment};

	if (minirt_array_builder_append(builder, 1, &node))
	{
		free(segment);
		free_builder(builder);
		return (true);
	}
	return (false);
}

static t_err	add_parent_node(t_minirt_array_builder *builder)
{
	const t_minirt_path_segment	node = {MINIRT_PATH_SEGMENT_PARENT, NULL};

	if (builder->length && ((t_minirt_path_segment *)builder->array)[
		builder->length - 1].type == MINIRT_PATH_SEGMENT_CHILD)
	{
		minirt_array_builder_remove_last(builder, 1);
		return (false);
	}
	if (minirt_array_builder_append(builder, 1, &node))
	{
		free_builder(builder);
		return (true);
	}
	return (false);
}

static t_err	add_node(
	const char *str,
	size_t segment_length,
	t_minirt_array_builder *builder
)
{
	char	*segment;

	if (minirt_starts_with(str, "./", NULL)
		|| minirt_str_eq(str, ".") || minirt_str_eq(str, ""))
		return (false);
	if (minirt_starts_with(str, "../", NULL)
		|| minirt_str_eq(str, ".."))
		return (add_parent_node(builder));
	if (minirt_strndup(str, segment_length, &segment))
		return (true);
	return (add_child_node(builder, segment));
}

t_err	minirt_path_parse(
	const char *str,
	t_minirt_path **out
)
{
	t_minirt_array_builder *const	builder
		= minirt_array_builder_new(sizeof(t_minirt_path_segment));
	size_t							i;
	size_t							segment_length;
	t_minirt_path					*result;

	i = 0;
	while (minirt_strchr(&str[i], '/', &segment_length))
		if (add_node(&str[i], segment_length, builder))
			return (true);
	result = malloc(sizeof(t_minirt_path));
	if (!result)
	{
		free_builder(builder);
		return (true);
	}
	result->length = builder->length;
	result->segments = minirt_array_builder_build(builder);
	free_builder(builder);
	if (!result->segments)
	{
		free(result);
		return (true);
	}
	*out = result;
	return (false);
}
