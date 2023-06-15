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

#include "minirt/common/array_builder.h"

#include <stdlib.h>

#include "minirt/common/libc.h"

static size_t	max(size_t a, size_t b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

static t_err	resize(t_minirt_array_builder *self, size_t minimum)
{
	const size_t	new_capacity = max(minimum, self->capacity * 2);
	void *const		new_array = malloc(self->item_size * new_capacity);

	if (!new_array)
		return (true);
	minirt_memcpy(new_array, self->array, self->item_size * self->length);
	free(self->array);
	self->array = new_array;
	self->capacity = new_capacity;
	return (false);
}

t_err	minirt_array_builder_append(
	t_minirt_array_builder *self,
	size_t length,
	const void *buf
)
{
	if (self->capacity - self->length < length
		&& resize(self, self->length + length))
		return (true);
	minirt_memcpy(
		&((char *)self->array)[self->item_size * self->length],
		buf,
		self->item_size * length);
	self->length += length;
	return (false);
}
